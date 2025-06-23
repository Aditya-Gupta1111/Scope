import QtQuick
import QtCharts

ChartView {
    id: chartView
    theme: ChartView.ChartThemeDark
    antialiasing: true
    animationOptions: ChartView.NoAnimation

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
        axisY: yAxis
        color: ch2Color
        width: 2
    }

    LineSeries {
        id: triggerLine
        name: "Trigger"
        axisX: xAxis
        axisY: yAxis
        color: triggerColor
        width: 1
        visible: showTriggerLine
    }

    function updateData(ch1Data, ch2Data) {
        ch1Series.clear()
        ch2Series.clear()

        if (!ch1Data || !ch2Data) return

        try {
            // Process CH1 data
            for (var i = 0; i < ch1Data.length; i++) {
                if (ch1Data[i] && typeof ch1Data[i].x === 'number' && typeof ch1Data[i].y === 'number') {
                    ch1Series.append(ch1Data[i].x, ch1Data[i].y / ch1Gain)
                }
            }

            // Process CH2 data
            for (var j = 0; j < ch2Data.length; j++) {
                if (ch2Data[j] && typeof ch2Data[j].x === 'number' && typeof ch2Data[j].y === 'number') {
                    ch2Series.append(ch2Data[j].x, ch2Data[j].y / ch2Gain)
                }
            }

            // Update trigger line
            if (showTriggerLine) {
                triggerLine.clear()
                triggerLine.append(0, triggerLevel)
                triggerLine.append(xAxis.max, triggerLevel)
            }
        } catch (error) {
            console.log("Error updating chart data:", error)
        }
    }

    function exportToCSV() {
        console.log("Export to CSV functionality - would save current data to file")
        // TODO: Implement actual CSV export
    }
}
