import QtQuick 1.0
Rectangle {
    id:root;
    property int smth:0
    color:"transparent"
    height: 26;
    property int rightSide:0
     Connections{
     target: application;
    onUpdateStatusBar:{
        var bat=(Math.floor(battery/10));
        batterytxt.text=battery+"%"
        switch (bat){
            case 0: imgbattery.source="status-icons/icon-s-status-battery-verylow.png";break;
            case 1: imgbattery.source="status-icons/icon-s-status-battery-low.png";break;
            case 2: imgbattery.source="status-icons/icon-s-status-battery1.png";break;
            case 3: imgbattery.source="status-icons/icon-s-status-battery2.png";break;
            case 4: imgbattery.source="status-icons/icon-s-status-battery3.png";break;
            case 5: imgbattery.source="status-icons/icon-s-status-battery4.png";break;
            case 6: imgbattery.source="status-icons/icon-s-status-battery5.png";break;
            case 7: imgbattery.source="status-icons/icon-s-status-battery6.png";break;
            case 8: imgbattery.source="status-icons/icon-s-status-battery7.png";break;
            case 9: imgbattery.source="status-icons/icon-s-status-battery8.png";break;
            case 10: imgbattery.source="status-icons/icon-s-status-battery8.png";break;
        }
        if (charging){imgbattery.source="status-icons/icon-s-status-charger.png";}
        var sig=Math.floor(network_signal/15);
        switch (sig){
            case 0:imgsignal.source="status-icons/icon-s-status-no-gsm-connection.png";break;
            case 1:imgsignal.source="status-icons/icon-s-status-network0.png";break;
            case 2:imgsignal.source="status-icons/icon-s-status-network1.png";break;
            case 3:imgsignal.source="status-icons/icon-s-status-network2.png";break;
            case 4:imgsignal.source="status-icons/icon-s-status-network3.png";break;
            case 5:imgsignal.source="status-icons/icon-s-status-network4.png";break;
            case 6:imgsignal.source="status-icons/icon-s-status-network5.png";break;
        }
        operator.text=opsos;
        switch (mode){
            case 0: imgmode.source="status-icons/icon-s-status-gsm-active.png";break;
            case 1: imgmode.source="status-icons/icon-s-status-3g-active.png";break;
            case 2: imgmode.source="status-icons/icon-s-status-wlan.png";break;
        }
        switch (profile){
            case 1: imgprofile.source="status-icons/icon-s-status-silent.png";break;
            case 5: imgprofile.source="status-icons/icon-s-status-offline.png";break;
            default: imgprofile.source="";break;
        }
        if (bt){imgbt.source="status-icons/icon-s-status-bluetooth.png";}
        else {imgbt.source="";}
    }
    }
    Row{
        spacing: 5;
        Image{
            id:imgbattery;
            source: "";
        }
        Text {
            id: batterytxt
            text: ""
            color:"white"
            font.pixelSize: 19;
        }
        Image{
            id:imgsignal;
            source: ""
        }
        Text{
            id:operator;
            color:"white"
            text:""
            font.pixelSize: 19;
        }
        Image {
            id: imgmode
            source: ""
        }
    }
    Row{
        spacing:5
        anchors.rightMargin: root.rightSide;
        anchors.right: root.right
        Image{
            id:imgbt
            source:""
        }
        Image{
            id:imgprofile
            source:""
        }
    }
}
