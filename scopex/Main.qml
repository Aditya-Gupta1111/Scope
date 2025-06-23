import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window
import ScopeX 1.0

ApplicationWindow {
    id: mainWindow
    width: 1200
    height: 800
    visible: true
    title: "Oscilloscope & Signal Generator"

    property color ch1Color: "red"
    property color ch2Color: "blue"
    property color triggerColor: "pink"
    property real triggerLevel: 0.0
    property bool showTriggerLine: true
    property bool isRunning: false
    property bool isConnected: false
    property bool sweepRunning: false
    property real ch1Gain: 1.0
    property real ch2Gain: 1.0
    property real ddsFrequency: 1000
    property int digitalOutputs: 0
    property int digitalInputs: 0
    property string statusMessage: "Ready"
    property int currentTab: 0
    SerialHandler {
        id: serialHandler
        onDataReceived: function(ch1Data, ch2Data) {
            scopeChart.updateData(ch1Data, ch2Data)
            if (currentTab === 1) { // DFT tab
                calculateDFT(ch1Data)
            }
        }
        onDftCalculated: function(dftData) {
            dftChart.updateData(dftData)
        }
        onDigitalInputsChanged: function(inputs) {
            digitalInputs = inputs
        }
        onConnectionChanged: {
            isConnected = serialHandler.connected
        }
        onStatusChanged: function(message) {
            statusMessage = message
        }
    }

    TabBar {
        id: tabBar
        width: parent.width
        TabButton { text: "Oscilloscope" }
        TabButton { text: "Signal Generator" }
        TabButton { text: "Digital I/O" }
        onCurrentIndexChanged: currentTab = currentIndex
    }

    StackLayout {
        anchors.top: tabBar.bottom
        anchors.bottom: statusBar.top
        width: parent.width
        currentIndex: tabBar.currentIndex

        // Oscilloscope Tab
        Item {
            ColumnLayout {
                anchors.fill: parent
                spacing: 5

                ScopeChart {
                    id: scopeChart
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    ch1Color: mainWindow.ch1Color
                    ch2Color: mainWindow.ch2Color
                    triggerColor: mainWindow.triggerColor
                    triggerLevel: mainWindow.triggerLevel
                    showTriggerLine: mainWindow.showTriggerLine
                }

                RowLayout {
                    Layout.fillWidth: true
                    height: 100

                    // Channel 1 Controls
                    GroupBox {
                        title: "Channel 1"
                        Layout.fillWidth: true
                        RowLayout {
                            ComboBox {
                                model: ["0.5x", "1x", "2x", "4x", "8x", "16x"]
                                onCurrentIndexChanged: ch1Gain = Math.pow(2, currentIndex - 1)
                            }
                            Slider {
                                id: ch1OffsetSlider
                                from: -512
                                to: 512
                                value: 0
                            }
                            Label { text: "Offset" }
                        }
                    }

                    // Channel 2 Controls
                    GroupBox {
                        title: "Channel 2"
                        Layout.fillWidth: true
                        RowLayout {
                            ComboBox {
                                model: ["0.5x", "1x", "2x", "4x", "8x", "16x"]
                                onCurrentIndexChanged: ch2Gain = Math.pow(2, currentIndex - 1)
                            }
                            Slider {
                                id: ch2OffsetSlider
                                from: -512
                                to: 512
                                value: 0
                            }
                            Label { text: "Offset" }
                        }
                    }

                    // Trigger Controls
                    GroupBox {
                        title: "Trigger"
                        Layout.fillWidth: true
                        ColumnLayout {
                            ComboBox {
                                model: ["Auto", "CH1", "CH2", "Ext"]
                                onCurrentIndexChanged: showTriggerLine = currentIndex === 1 || currentIndex === 2
                            }
                            ComboBox {
                                model: ["Rising", "Falling"]
                            }
                            Slider {
                                id: trigLevelSlider
                                from: -10
                                to: 10
                                value: 0
                                onValueChanged: triggerLevel = value
                            }
                            Label { text: "Level: " + triggerLevel.toFixed(2) }
                        }
                    }

                    // Timebase Controls
                    GroupBox {
                        title: "Timebase"
                        Layout.fillWidth: true
                        ComboBox {
                            model: [
                                "2Mbps 0.5µs", "1Mbps 1µs", "500kbps 2µs", "200kbps 5µs",
                                "100kbps 10µs", "50kbps 20µs", "20kbps 50µs", "10kbps 100µs",
                                "5kbps 200µs", "2kbps 500µs", "1kbps 1ms", "500Hz 2ms",
                                "200Hz 5ms", "100Hz 10ms"
                            ]
                        }
                    }

                    // Display Controls
                    GroupBox {
                        title: "Display"
                        Layout.fillWidth: true
                        ColumnLayout {
                            ComboBox {
                                model: ["CH1+CH2", "CH1", "CH2", "XY", "CH1 DFT", "CH2 DFT"]
                            }
                            CheckBox { text: "Overplot" }
                            CheckBox { text: "Storage" }
                        }
                    }
                }

                RowLayout {
                    Layout.fillWidth: true
                    Button {
                        text: isRunning ? "Stop" : "Run"
                        onClicked: {
                            if (isRunning) {
                                serialHandler.stopCapture()
                            } else {
                                serialHandler.runCapture(false)
                            }
                            isRunning = !isRunning
                        }
                    }
                    Button {
                        text: "Single"
                        onClicked: serialHandler.runCapture(false)
                    }
                    Button {
                        text: "Continuous"
                        onClicked: serialHandler.runCapture(true)
                    }
                    Button {
                        text: "Export CSV"
                        onClicked: scopeChart.exportToCSV()
                    }
                }
            }
        }

        // Signal Generator Tab
        Item {
            ColumnLayout {
                anchors.fill: parent
                spacing: 5

                DFTChart {
                    id: dftChart
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                }

                RowLayout {
                    Layout.fillWidth: true

                    // Waveform Controls
                    GroupBox {
                        title: "Waveform"
                        Layout.fillWidth: true
                        ColumnLayout {
                            ComboBox {
                                model: ["Sine", "Square", "Triangle", "Ramp Up", "Ramp Down", "Arbitrary"]
                                onCurrentIndexChanged: serialHandler.setDDSWaveform(currentIndex)
                            }
                            Button {
                                text: "Load Arbitrary"
                                onClicked: console.log("Load Arbitrary waveform")
                            }
                        }
                    }

                    // Frequency Controls
                    GroupBox {
                        title: "Frequency"
                        Layout.fillWidth: true
                        ColumnLayout {
                            TextField {
                                text: ddsFrequency.toString()
                                validator: DoubleValidator { bottom: 1; top: 50000 }
                                onEditingFinished: ddsFrequency = parseFloat(text)
                            }
                            Button {
                                text: "Set Frequency"
                                onClicked: serialHandler.setDDSFrequency(ddsFrequency)
                            }
                            Button {
                                text: sweepRunning ? "Stop Sweep" : "Start Sweep"
                                onClicked: {
                                    if (sweepRunning) {
                                        serialHandler.stopSweep()
                                    } else {
                                        serialHandler.startSweep(
                                            parseFloat(startFreqField.text),
                                            parseFloat(endFreqField.text),
                                            parseInt(stepsField.text),
                                            parseInt(delayField.text)
                                        )
                                    }
                                    sweepRunning = !sweepRunning
                                }
                            }
                        }
                    }

                    // Sweep Settings
                    GroupBox {
                        title: "Sweep Settings"
                        Layout.fillWidth: true
                        enabled: !sweepRunning
                        GridLayout {
                            columns: 2
                            Label { text: "Start (Hz):" }
                            TextField { id: startFreqField; text: "100" }
                            Label { text: "End (Hz):" }
                            TextField { id: endFreqField; text: "10000" }
                            Label { text: "Steps:" }
                            TextField { id: stepsField; text: "100" }
                            Label { text: "Delay (ms):" }
                            TextField { id: delayField; text: "100" }
                        }
                    }
                }

                RowLayout {
                    Layout.fillWidth: true
                    Button {
                        text: "Run DDS"
                        onClicked: serialHandler.runDDS()
                    }
                    Button {
                        text: "Stop DDS"
                        onClicked: serialHandler.stopDDS()
                    }
                }
            }
        }

        // Digital I/O Tab
        Item {
            ColumnLayout {
                anchors.fill: parent
                spacing: 10

                GridLayout {
                    columns: 2
                    Layout.fillWidth: true

                    // Digital Outputs
                    GroupBox {
                        title: "Digital Outputs"
                        Layout.fillWidth: true
                        GridLayout {
                            columns: 4
                            Repeater {
                                model: 4
                                Button {
                                    text: (digitalOutputs & (1 << index)) ? "H" : "L"
                                    onClicked: {
                                        digitalOutputs ^= (1 << index)
                                        serialHandler.setDigitalOutputs(digitalOutputs)
                                    }
                                }
                            }
                        }
                    }

                    // Digital Inputs
                    GroupBox {
                        title: "Digital Inputs"
                        Layout.fillWidth: true
                        GridLayout {
                            columns: 4
                            Repeater {
                                model: 4
                                Rectangle {
                                    width: 30
                                    height: 30
                                    radius: 15
                                    color: (digitalInputs & (1 << index)) ? "green" : "red"
                                    border.color: "black"
                                }
                            }
                        }
                    }
                }

                GroupBox {
                    title: "Signature"
                    Layout.fillWidth: true
                    Column {
                        width: parent.width
                        TextField {
                            width: parent.width
                            placeholderText: "Enter your name"
                        }
                        Text {
                            text: "Device ID: " + (isConnected ? "Connected" : "Disconnected")
                        }
                    }
                }

                Button {
                    text: "Read Inputs"
                    onClicked: serialHandler.readDigitalInputs()
                }
            }
        }
    }

    // Status Bar
    Rectangle {
        id: statusBar
        anchors.bottom: parent.bottom
        width: parent.width
        height: 30
        color: "#f0f0f0"

        RowLayout {
            anchors.fill: parent
            spacing: 10

            // COM Port Controls
            ComboBox {
                id: portCombo
                model: serialHandler.availablePorts
                onActivated: function(index) {
                    // Handle port selection
                }
            }

            Button {
                text: "Refresh"
                onClicked: serialHandler.refreshPorts()
            }

            Button {
                text: "Connect"
                enabled: portCombo.currentIndex >= 0 && !isConnected
                onClicked: serialHandler.connectToPort(portCombo.currentText)
            }

            Button {
                text: "Disconnect"
                enabled: isConnected
                onClicked: serialHandler.disconnectPort()
            }

            Label {
                text: statusMessage
                Layout.fillWidth: true
            }
        }
    }
}
