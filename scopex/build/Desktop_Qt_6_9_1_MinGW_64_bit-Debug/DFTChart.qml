import QtQuick
import QtCharts

ChartView {
    id: dftChart
    theme: ChartView.ChartThemeDark
    antialiasing: true

    ValueAxis {
        id: dftXAxis
        min: 0
        max: 10000
        titleText: "Frequency (Hz)"
    }

    ValueAxis {
        id: dftYAxis
        min: 0
        max: 10
        titleText: "Magnitude"
    }

    LineSeries {
        id: dftSeries
        axisX: dftXAxis
        axisY: dftYAxis
        color: "yellow"
        width: 2
    }

    function updateData(dftData) {
        dftSeries.clear()
        if (!dftData) return
        
        for (var i = 0; i < dftData.length; i++) {
            if (dftData[i] && dftData[i].x !== undefined && dftData[i].y !== undefined) {
                dftSeries.append(dftData[i].x, dftData[i].y)
            }
        }
    }
}