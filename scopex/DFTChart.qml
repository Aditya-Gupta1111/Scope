import QtQuick
import QtCharts

ChartView {
    id: dftChart
    theme: ChartView.ChartThemeDark
    antialiasing: true
    animationOptions: ChartView.NoAnimation

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

        try {
            var maxMag = 0

            // First pass: find maximum magnitude for scaling
            for (var i = 0; i < dftData.length; i++) {
                if (dftData[i] && typeof dftData[i].y === 'number') {
                    if (dftData[i].y > maxMag) {
                        maxMag = dftData[i].y
                    }
                }
            }

            // Update Y-axis scale
            if (maxMag > 0) {
                dftYAxis.max = Math.ceil(maxMag * 1.1) // Add 10% headroom
            }

            // Second pass: add data points
            for (var j = 0; j < dftData.length; j++) {
                if (dftData[j] && typeof dftData[j].x === 'number' && typeof dftData[j].y === 'number') {
                    dftSeries.append(dftData[j].x, dftData[j].y)
                }
            }
        } catch (error) {
            console.log("Error updating DFT chart data:", error)
        }
    }
}
