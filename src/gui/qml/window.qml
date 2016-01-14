import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.2
// import QtQuick.Window 2.2
//import QtQuick.Dialogs 1.2
import "UI.js" as UI

ApplicationWindow {
    title: qsTr("Trainer Helper")
    width: 800
    height: 600
    visible: true

    Rectangle {
        id: profileSelection
        x: profileSelectionButton.x
        y: profileSelectionButton.y
        z: 1000000000
        width: profileSelectionButton.width
        height: profileSelectionButton.height
        color: "transparent"
        property bool enlarged: false

        states: State {
            name: "collapsed"; when: profileSelection.enlarged == true
            PropertyChanges { target: profileSelection; width: 500; height: 300; color: "yellow" }
        }

        transitions: Transition {
            from: ""; to: "collapsed"; reversible: true
            ParallelAnimation {
                NumberAnimation { id: sizeAnimation; properties: "width,height"; duration: 250; easing.type: Easing.InOutCubic }
                ColorAnimation { duration: sizeAnimation.duration; easing.type: sizeAnimation.easing.type; }
            }
        }
    }

    RowLayout {
        anchors.fill: parent
        spacing: 6

        ColumnLayout {

            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.minimumWidth: 50
            Layout.preferredWidth: 100
            Layout.maximumWidth: 300
            Layout.minimumHeight: 150

            spacing: 12

            // Profile selection
            Rectangle {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.minimumHeight: 50
                Layout.preferredHeight: 50
                Layout.maximumHeight: 50
                Layout.alignment: Qt.AlignTop

                color: 'red'

                Button {
                    id: profileSelectionButton
                    anchors.centerIn: parent
                    text: "Inpit data"
                    onClicked: {
                        console.log("Enlarge");
                        profileSelection.enlarged = !profileSelection.enlarged;
                    }
                }
            }

            // Profile details
            Rectangle {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.minimumHeight: 50
                Layout.preferredHeight: 200

                color: 'teal'

                Text {
                    anchors.centerIn: parent
                    text: ""
                }
            }
        }

        ColumnLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.minimumWidth: 100
            Layout.preferredWidth: 200
            Layout.preferredHeight: 100

            Rectangle {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.minimumHeight: 10
                color: "transparent"

                Text {
                    anchors.centerIn: parent
                    text: "Players"
                }
            }

            ScrollView {
                Layout.fillWidth: true
                Layout.fillHeight: true

                ListView {
                    model: playerList
                    header: bannercomponent
                    footer: Rectangle {
                        width: parent.width; height: 30;
                        gradient: clubcolors
                    }
                    delegate: playerDelegate
                }
            }
        }
    }

    Component {
        id: playerDelegate
        Item {
            property variant profileData: model
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
                onClicked: profileListView.currentIndex = index
            }
        }

    }
}
