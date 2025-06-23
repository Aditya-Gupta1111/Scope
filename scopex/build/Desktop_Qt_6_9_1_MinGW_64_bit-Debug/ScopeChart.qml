import QtQuick
import QtCharts

ChartView {
    id: chartView
    theme: ChartView.ChartThemeDark
    antialiasing: true
    animationOptions: ChartView.NoAnimation

    property alias ch1Series: ch1Series
    property alias ch2Series: ch2Series
    property alias triggerLine: triggerLine
    property color ch1Color: "red"
    property color ch2Color: "blue"
    property color triggerColor: "pink"
    property real ch1Gain: 1.0
    property real ch2Gain: 1.0
    property real triggerLevel: 0.0
    property bool showTriggerLine: true

    ValueAxis {
        id: xAxis
        min: 0
        max: 200
        titleText: "Time (µs)"
    }

    ValueAxis {
        id: yAxis
        min: -10
        max: 10
        titleText: "Voltage (V)"
    }

    LineSeries {
        id: ch1Series
        name: "CH1"
        axisX: xAxis
        axisY: yAxis
        color: ch1Color
        width: 2
    }

    LineSeries {
        id: ch2Series
        name: "CH2"
        axisX: xAxis
        axisYRight: yAxis
        color: ch2Color
        width: 2
    }

    ScatterSeries {
        id: triggerLine
        name: "Trigger"
        axisX: xAxis
        axisY: yAxis
        color: triggerColor
        markerSize: 10
        visible: showTriggerLine
    }

    function updateData(ch1Data, ch2Data) {
        ch1Series.clear()
        ch2Series.clear()

        if (!ch1Data || !ch2Data) return

        for (var i = 0; i < ch1Data.length; i++) {
            if (ch1Data[i] && ch1Data[i].x !== undefined && ch1Data[i].y !== undefined) {
                ch1Series.append(ch1Data[i].x, ch1Data[i].y / ch1Gain)
            }
        }

        for (var j = 0; j < ch2Data.length; j++) {
            if (ch2Data[j] && ch2Data[j].x !== undefined && ch2Data[j].y !== undefined) {
                ch2Series.append(ch2Data[j].x, ch2Data[j].y / ch2Gain)
            }
        }

        if (showTriggerLine) {
            triggerLine.clear()
            triggerLine.append(0, triggerLevel)
            triggerLine.append(xAxis.max, triggerLevel)
        }
    }

    function exportToCSV() {
        // CSV export implementation
        console.log("Export to CSV functionality would go here")
    }
}