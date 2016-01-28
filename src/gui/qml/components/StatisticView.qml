import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.2
import org.covolunablu 1.0

Rectangle {
    property Statistic statistic
    id: banner
    Layout.fillWidth: true
    Layout.fillHeight: true
    Layout.minimumWidth: 100
    Layout.minimumHeight: 100
    border {color: "#9EDDF2"; width: 2}
    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10
        Text {
            //title
            Layout.fillWidth: true
            Layout.minimumWidth: 100
//            Layout.minimumHeight: 100
            font.bold: true
            text: statistic.getName();
        }
        Text {
            Layout.fillWidth: true
            Layout.minimumWidth: 100
//            Layout.minimumHeight: 100
            visible: statistic.isNormal
            text: "Normal"
        }
        Text {
            Layout.fillWidth: true
            Layout.minimumWidth: 100
//            Layout.minimumHeight: 100
            visible: statistic.isOutstanding
            color: statistic.isOutstandingGood ? "green" : "red"
            text: "outstanding: " + (statistic.isOutstandingGood ? "GOOD" : "BAD")
        }
        Text {
            Layout.fillWidth: true
            Layout.minimumWidth: 100
//            Layout.minimumHeight: 100
            visible: statistic.hasSuddenChanged
            color: statistic.hasSuddenChangedGood ? "green" : "red"
            text: "sudden change: " + (statistic.hasSuddenChangedGood ? "GOOD" : "BAD")
        }
        Text {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.minimumWidth: 100
            Layout.minimumHeight: 100
            text: "history: "// + JSON.stringify(statistic, undefined, "  ")
        }
        Text {
            Layout.fillWidth: true
            Layout.minimumWidth: 100
//            Layout.minimumHeight: 100
            text: "Average: " + statistic.averageValue
        }
    }
}

