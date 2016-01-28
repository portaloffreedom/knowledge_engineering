/**
 * Created by matteo on 08/01/16.
 */

function selectedPlayer() {
    //console.log(JSON.stringify(playerListView));
    return playerListView.currentItem.playerData;
}

function clearForm() {
    name_field.text = "";
    surname_field.text = "";
    height_field.value = 100;
    special_field.checked = false;
}

function addMeasurement(player) {
    addMeasurementWindow.playerData = player;
    addMeasurementWindow.visible = true;
}

function insertMeasurement(player, exercise, raw_value) {
    console.log("taking value: " + raw_value);
    var measurement = exercise.createMeasurement(raw_value);
    console.log("typeof measurement: " + typeof (measurement))
    console.log(JSON.stringify(measurement));
    console.log("typeof player: " + typeof (player));
    //console.log(JSON.stringify(player, null, "  "));
    appController.insertMeasurement(playerListView.currentIndex, measurement);
}
