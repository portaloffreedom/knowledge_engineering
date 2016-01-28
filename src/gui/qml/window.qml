import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.2
import QtQuick.Window 2.2
//import QtQuick.Dialogs 1.2
import org.covolunablu 1.0
import "js/UI.js" as UI
import "components"

ApplicationWindow {
    title: qsTr("Trainer Helper")
    width: 1024
    height: 600
    minimumWidth: 700
    minimumHeight: 400
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

                RowLayout {
                    Layout.fillWidth: true

                    Button {
                        // Confirm adding player
                        //Layout.alignment: Qt.AlignLeft
                        text: qsTr("Cancel")
                        onClicked: {
                            //TODO create player and save it in the list
                            player_creation.enlarged = false
                            //UI.clearForm();
                        }
                    }

                    Rectangle {
                        Layout.fillWidth: true
                    }

                    Button {
                        // Confirm adding player
                        //Layout.alignment: Qt.AlignRight
                        text: qsTr("Add player")
                        onClicked: {
                            //TODO create player and save it in the list
                            player_creation.enlarged = false
                            appController.createPlayer(name_field.text, surname_field.text, height_field.value, null, special_field.checked);
                            UI.clearForm();
                        }
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

            Button {
                text: "+"
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                width: 40
                onClicked: UI.addMeasurement(model);
            }
        }

    }

     Window {
         id: addMeasurementWindow
         property variant playerData
         property list<Exercise> exercises: [
             Exercise {
                 name: "Shuttle test"
                 description: "shuttle run test met 4 pylonnen in t formaat; vooruit, links,omdraaien en naar andere kant, midden, terug"
                 measurementUnit: "s"
                 minimum: 10
                 maximum: 30
                 average: 18
                 type: "dribbling"
             },
             Exercise {
                 name: "Balance Beam"
                 description: "snelheid over een evenwichtsbalk heen en terug zonder vallen"
                 measurementUnit: "s"
                 minimum: 7
                 maximum: 60
                 average: 20
                 type: "dribbling"
             },
             Exercise {
                 name: "Reaction Time"
                 description: "reactiesnelheid. Met rug naar trainer; signaal geven, bal een kant op schoppen en aannemen. % goed gemeten"
                 measurementUnit: "%"
                 minimum: 0
                 maximum: 100
                 average: 50
                 type: "dribbling"
             },
             Exercise {
                 name: "Keep uppie"
                 description: "aantal keer hooghouden"
                 measurementUnit: ""
                 minimum: 1
                 maximum: 100
                 average: 5
                 type: "dribbling"
             },
             Exercise {
                 name: "Shuttle dribble"
                 description: "snelheid tussen 10 pylonnetjes slalommen heen en terug"
                 measurementUnit: "s"
                 minimum: 25
                 maximum: 60
                 average: 40
                 type: "dribbling"
             },
             Exercise {
                 name: "Game Positioning"
                 description: "vrjie ruimte zoeken tijdens een wedstrijd op schaal van nooit vrij tot vaak vrij"
                 measurementUnit: ""
                 minimum: 1
                 maximum: 10
                 average: 5
                 type: "shooting"
             },
             Exercise {
                 name: "1v1 attacking"
                 description: "1v1 attacking versus player of same age; percentage won"
                 measurementUnit: "%"
                 minimum: 0
                 maximum: 100
                 average: 50
                 type: "shooting"
             },
             Exercise {
                 name: "Shot distance"
                 description: "voorbeeld: afstand dat een voetbal kan worden geschopt?"
                 measurementUnit: "m"
                 minimum: 2
                 maximum: 100
                 average: 40
                 type: "shooting"
             },
             Exercise {
                 name: "Long shots"
                 description: "goed gemikte schoten in de hoek op goal vanaf 20 meter "
                 measurementUnit: "%"
                 minimum: 0
                 maximum: 100
                 average: 35
                 type: "shooting"
             },
             Exercise {
                 name: "Volley s"
                 description: "percentage goed op doel geschoten na een hoog aangespeelde bal vanaf 10 meter"
                 measurementUnit: "%"
                 minimum: 0
                 maximum: 100
                 average: 30
                 type: "shooting"
             },
             Exercise {
                 name: "Penalities"
                 description: "percentage goed gemikt in de hoek met keeper in midden"
                 measurementUnit: "%"
                 minimum: 0
                 maximum: 100
                 average: 30
                 type: "shooting"
             },
             Exercise {
                 name: "High jump"
                 description: "Afstand die vanuit stilstand kan worden gesprongen (hoogte)"
                 measurementUnit: "cm"
                 minimum: 10
                 maximum: 100
                 average: 30
                 type: "physical"
             },
             Exercise {
                 name: "Burpees"
                 description: "amount of burpees that can be done in 2 minutes"
                 measurementUnit: ""
                 minimum: 10
                 maximum: 30
                 average: 15
                 type: "physical"
             },
             Exercise {
                 name: "Plate push"
                 description: "gewicht van 20kg duwen? hoeveel meter in 60 seconden?"
                 measurementUnit: "m"
                 minimum: 20
                 maximum: 60
                 average: 25
                 type: "physical"
             },
             Exercise {
                 name: "1v1 duel"
                 description: "duels die worden gewonnen; op knieen en winnen is ander op de grond krijgen, %"
                 measurementUnit: "%"
                 minimum: 0
                 maximum: 100
                 average: 50
                 type: "physical"
             },
             Exercise {
                 name: "Free player notice"
                 description: "being able to notice free players on a scale of 1-10"
                 measurementUnit: ""
                 minimum: 1
                 maximum: 10
                 average: 5
                 type: "passing"
             },
             Exercise {
                 name: "Opposite pass"
                 description: "being able to pass to the opposite side of the field accurately"
                 measurementUnit: "%"
                 minimum: 0
                 maximum: 100
                 average: 50
                 type: "passing"
             },
             Exercise {
                 name: "Free kicks"
                 description: "amount of times scored when shooting over a 1,5m high wall at 3m distance, 10m to goal"
                 measurementUnit: "%"
                 minimum: 0
                 maximum: 100
                 average: 25
                 type: "passing"
             },
             Exercise {
                 name: "Short passing 5m"
                 description: "accuracy at 5m % correctly passed"
                 measurementUnit: "%"
                 minimum: 0
                 maximum: 100
                 average: 70
                 type: "passing"
             },
             Exercise {
                 name: "Long passing 15m"
                 description: "accuracy at 15m % correctly passed"
                 measurementUnit: "%"
                 minimum: 0
                 maximum: 100
                 average: 20
                 type: "passing"
             },
             Exercise {
                 name: "Curve shooting"
                 description: "vanaf zijlijn hoeveel effect aan een bal kan worden gegeven. Gemeten in afwijking vanaf lijn (moet recht vooruit de bal schieten)"
                 measurementUnit: "m"
                 minimum: 2
                 maximum: 20
                 average: 5
                 type: "passing"
             },
             Exercise {
                 name: "100m dash"
                 description: "snelheid waarin 100m wordt gerend vanuit stilstand"
                 measurementUnit: "s"
                 minimum: 11
                 maximum: 19
                 average: 13
                 type: "pace"
             },
             Exercise {
                 name: "Maximum sprint speed"
                 description: "topsnelheid berekenen"
                 measurementUnit: "km/h"
                 minimum: 15
                 maximum: 35
                 average: 20
                 type: "pace"
             },
             Exercise {
                 name: "1v1 ball possession"
                 description: "2 players start running forward, trainer passes ball to them and amount of times player gets posession"
                 measurementUnit: "%"
                 minimum: 0
                 maximum: 100
                 average: 50
                 type: "defending"
             },
             Exercise {
                 name: "Heading test"
                 description: "footballs correctly headed in the right corner of the goal "
                 measurementUnit: ""
                 minimum: 0
                 maximum: 100
                 average: 30
                 type: "defending"
             },
             Exercise {
                 name: "Location test"
                 description: "put a player in the centre of the field, blindfold him and let him walk towards the penalty line; Percentage in devation from total distance walked and difference between goal distance."
                 measurementUnit: ""
                 minimum: 0
                 maximum: 100
                 average: 30
                 type: "defending"
             },
             Exercise {
                 name: "1v1 circle duel"
                 description: "ball in the middle between 2 players; they have to use their body without hands to gain posession and play to their side"
                 measurementUnit: ""
                 minimum: 0
                 maximum: 100
                 average: 50
                 type: "defending"
             },
             Exercise {
                 name: "sliding distance"
                 description: "distance that can be slid through a tackle from a 3m run lane"
                 measurementUnit: "m"
                 minimum: 1
                 maximum: 2
                 average: 1.2
                 type: "defending"
             }
         ]

         title: qsTr("Add measurement for ") + playerData.name
         modality: Qt.ApplicationModal
         width: 300
         height: 200
         visible: false

         GroupBox {
             anchors.fill: parent
             title: qsTr("Insert new measurement for player ") + playerData.name

             ColumnLayout {
                 anchors.fill: parent

                 ComboBox {
                     id: exerciseSelection
                     model: addMeasurementWindow.exercises
                     focus: true
                     textRole: "name"
                 }

                 Text {
                     Layout.fillWidth: true
                     width: 100
                     text: addMeasurementWindow.exercises[exerciseSelection.currentIndex].description
                     wrapMode: Text.WordWrap
                 }

                 RowLayout {
                     Label { text: qsTr("measurement")}
                     SpinBox {
                        id: measurement_raw_value
                        decimals: 2
                        maximumValue: addMeasurementWindow.exercises[exerciseSelection.currentIndex].maximum
                        minimumValue: addMeasurementWindow.exercises[exerciseSelection.currentIndex].minimum
                        value: addMeasurementWindow.exercises[exerciseSelection.currentIndex].average
                     }
                     Label {
                         Layout.fillWidth: true
                         text: addMeasurementWindow.exercises[exerciseSelection.currentIndex].measurementUnit
                     }
                 }

                 RowLayout {
                     Layout.fillWidth: true

                     Button {
                         text: qsTr("Cancel")
                         onClicked: addMeasurementWindow.visible = false;
                     }
                     Button {
                         text: qsTr("Insert")
                         onClicked: {
                             UI.insertMeasurement(
                                         addMeasurementWindow.playerData,
                                         addMeasurementWindow.exercises[exerciseSelection.currentIndex],
                                         measurement_raw_value.value
                                         )
                             addMeasurementWindow.visible = false;
                         }
                     }
                 }

                 Text {
                     text: JSON.stringify(addMeasurementWindow.exercises[exerciseSelection.currentIndex], null, "  ")
                 }
             }
         }
     }
}
