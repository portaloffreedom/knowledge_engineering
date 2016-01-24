import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.2
// import QtQuick.Window 2.2
//import QtQuick.Dialogs 1.2
import org.covolunablu 1.0
import "js/UI.js" as UI
import "components"

ApplicationWindow {
    title: qsTr("Trainer Helper")
    width: 800
    height: 600
    visible: true

    Rectangle {
        id: player_creation
        x: player_creation_button.x + player_creation_button.anchors.leftMargin
        y: player_creation_button.y + player_creation_button.anchors.topMargin
        z: 1000000000
        //width: player_creation_button.width
        //height: player_creation_button.height
        //color: "white"
        opacity: 0
        property bool enlarged: false

        MouseArea {
            // capturing input so it doens't do transparent things
            id: player_creation_mouse_area
            anchors.fill: player_creation_group_box
            enabled: false
            //onClicked: {} //ignore input
        }

        states: State {
            name: "collapsed"; when: player_creation.enlarged == true
            PropertyChanges {
                target: player_creation
                //width: 500; height: 300
                opacity: 1
            }
            PropertyChanges {
                target: player_creation_mouse_area
                enabled: true
            }
            PropertyChanges {
                target: name_field
                enabled: true
            }
            PropertyChanges {
                target: surname_field
                enabled: true
            }
            PropertyChanges {
                target: special_field
                enabled: true
            }
            PropertyChanges {
                target: height_field
                enabled: true
            }
        }

        transitions: Transition {
            from: ""; to: "collapsed"; reversible: true
            ParallelAnimation {
                OpacityAnimator { id: opacityAnimation; duration: 250; easing.type: Easing.InOutCubic }
                NumberAnimation { properties: "width,height"; duration: opacityAnimation.duration; easing.type: opacityAnimation.easing.type; }
            }
        }

        GroupBox {
            id: player_creation_group_box
            title: qsTr("Insert new Player")
            width: 500
            ColumnLayout {
                id: column
                anchors.fill: parent

                TextField {
                    id: name_field
                    enabled: false
                    Layout.fillWidth: true
                    placeholderText: qsTr("Name")
                }

                TextField {
                    id: surname_field
                    enabled: false
                    Layout.fillWidth: true
                    placeholderText: qsTr("Surname")
                }

                RowLayout {
                    Layout.fillWidth: true
                    Label { text: qsTr("Special"); Layout.fillWidth: true }
                    Switch { id: special_field; enabled: false; checked: false }
                }

                SpinBox { id: height_field; enabled: false; value: 100; minimumValue: 0; maximumValue: 300; Layout.fillWidth: true}

                Button {
                    // Confirm adding player
                    Layout.alignment: Qt.AlignRight
                    text: qsTr("Add player")
                    onClicked: {
                        //TODO create player and save it in the list
                        player_creation.enlarged = false
                        appController.createPlayer(name_field.text, surname_field.text, height_field.value, null, special_field.checked);
                    }
                }
            }
        }
    }

    RowLayout {
        anchors.fill: parent
        spacing: 6

        // Player List (and creation)
        ColumnLayout {

            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.minimumWidth: 50
            Layout.preferredWidth: 100
            Layout.maximumWidth: 300
            Layout.minimumHeight: 150

            spacing: 12

            // Player creation
            Rectangle {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.minimumHeight: 50
                Layout.preferredHeight: 50
                Layout.maximumHeight: 50
                Layout.alignment: Qt.AlignTop
                Layout.leftMargin: 10;
                Layout.rightMargin: 10;
                color: "transparent"

                Text {
                    id: players_title
                    anchors.verticalCenter: parent.verticalCenter
                    text: qsTr("Players")
                    font.bold: true
                }

                Button {
                    id: player_creation_button
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: players_title.right
                    anchors.leftMargin: 10;
                    text: qsTr("Add Player")
                    onClicked: {
                        console.log("Enlarge");
                        player_creation.enlarged = !player_creation.enlarged;
                    }
                }
            }

            // Player List
            ScrollView {
                Layout.fillWidth: true
                Layout.fillHeight: true

                ListView {
                    id: playerListView
                    model: appController.players
                    highlight: Rectangle {
                        color: "lightsteelblue"
                        //radius: 5
                    }
                    delegate: playerDelegate
                }
            }
        }

        // Player Details
        ColumnLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.minimumWidth: 100
            Layout.preferredWidth: 200
            Layout.preferredHeight: 100
            Layout.alignment: Qt.AlignTop

            Rectangle {
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignTop
                Layout.minimumHeight: 40

                color: 'teal'

                Text {
                    anchors.centerIn: parent
                    font.bold: true
                    text: UI.selectedPlayer().name + " " + UI.selectedPlayer().surname
                }
            }

            GridLayout {
                Layout.fillWidth: true
                Layout.fillHeight: true
                rows: 2
                columns: 3

                StatisticView {
                    statistic: UI.selectedPlayer().statistics.defending
                }

                StatisticView {
                    statistic: UI.selectedPlayer().statistics.dribbling
                }

                StatisticView {
                    statistic: UI.selectedPlayer().statistics.pace
                }

                StatisticView {
                    statistic: UI.selectedPlayer().statistics.passing
                }

                StatisticView {
                    statistic: UI.selectedPlayer().statistics.physical
                }

                StatisticView {
                    statistic: UI.selectedPlayer().statistics.shooting
                }
            }
        }
    }

    Component {
        id: playerDelegate
        Item {
            property variant playerData: model
            id: playerItem
            width: parent.width; height: child.height+10
            Column {
                anchors.left: parent.left
                anchors.leftMargin: 8
                anchors.verticalCenter: parent.verticalCenter
                id: child
                Text { text: '<b>' + model.name + " " + model.surname
                        + (model.special ? " (" + qsTr("special") + ")" : "") + '</b>'}
                Text { text: 'Height: <i>' + model.height + '</i>'}
            }

            MouseArea {
                anchors.fill: parent
                onClicked: playerListView.currentIndex = index
            }
        }

    }
}
