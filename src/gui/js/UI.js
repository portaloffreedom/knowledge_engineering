/**
 * Created by matteo on 08/01/16.
 */

function selectedPlayer() {
    //console.log(JSON.stringify(playerListView))
    return playerListView.currentItem.playerData;
}

function clearForm() {
    name_field.text = ""
    surname_field.text = ""
    height_field.value = 100
    special_field.checked = false
}
