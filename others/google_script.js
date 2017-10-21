var SCRIPT_PROP = PropertiesService.getScriptProperties(); 

function doGet(e){
  return handleResponse(e);
}

function doPost(e){
  return handleResponse(e);
}

function handleResponse(e) {
  
  var lock = LockService.getPublicLock();
  lock.waitLock(30000); 
  
  try {
    
    var data = e.parameter;
        
    var doc = SpreadsheetApp.openById(SCRIPT_PROP.getProperty("key"));
    
    //Shorten the Device ID for security
    var deviceID = data["deviceID"];
    deviceID = deviceID.substring(0, 5);
    
    var sheet = doc.getSheetByName(deviceID);
    
    if (sheet == null) {
      //Create a new sheet with the device's name if it does not exist
      sheet = doc.insertSheet();
      sheet.setName(deviceID);
    }
    
    setNextRow(data,sheet);

    return ContentService
          .createTextOutput(JSON.stringify({"result":"success"}))
          .setMimeType(ContentService.MimeType.JSON);
  } catch(e){
    // if error return this
    return ContentService
          .createTextOutput(JSON.stringify({"result":"error", "error": e}))
          .setMimeType(ContentService.MimeType.JSON);
  } finally { //release lock
    lock.releaseLock();
  }
}

function setNextRow(data,sheet) {
  
  var nextRow = sheet.getLastRow() + 1;
    
  var row = [];
  
  row.push(new Date());
  
  var readings = data["readings"].split(",");
  
  for (var i = 0; i < readings.length; i++) {
    
    var reading = readings[i]
    
    if (reading == -127 || reading == 0) {
      row.push("ERROR");
    } else {
      row.push(reading) 
    }
  }

  sheet.getRange(nextRow, 1, 1, row.length).setValues([row]);
}

function setup() {
    var doc = SpreadsheetApp.getActiveSpreadsheet();
    SCRIPT_PROP.setProperty("key", doc.getId());
}