function doGet(e) {
  var ss = SpreadsheetApp.getActiveSpreadsheet();
  var sheet = ss.getSheetByName("dados");

  if (!sheet) {
    sheet = ss.insertSheet("dados");
    sheet.appendRow(["data_hora", "temperatura_c", "led"]);
  }

  var temp = e.parameter.temp || "";
  var led = e.parameter.led || "";
  var agora = new Date();

  sheet.appendRow([agora, temp, led]);

  return ContentService
    .createTextOutput("OK")
    .setMimeType(ContentService.MimeType.TEXT);
}
