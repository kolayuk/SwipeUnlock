import Qt 4.7

Item {
    id: clock
    width : parent.width
    height : columnLayout.height
    property color textColor : "white"
    property int fontSize : 60
    property int fontSizeDate: 15
    property variant hours : "00:00"
    property variant minutes : "00"
    property variant seconds : ""

    property string date: ""
    property variant shift : 0
    property bool showSeconds : true
    property bool showDate : true
    function timeChanged() {
        // To be fixed to fit locale
        var Month = new Array(strings[7], strings[8], strings[9], strings[10],strings[11], strings[12],strings[13],strings[14], strings[15],strings[16], strings[17],strings[18]);
        var Days = new Array(strings[6],strings[0], strings[1], strings[2], strings[3],strings[4], strings[5],"gg");
        var d = new Date;
        timer.interval=calcSecsToMin()*1000;
        clock.hours=application.getTime();
        date=lang!=16?application.GetDate():Days[d.getDay()]+", "+d.getDate() + " " + Month[d.getMonth()] + " " + d.getFullYear();
    }

    function checkTime(i) {
        return (i<10) ? "0"+i : i;
    }
    function calcSecsToMin(){
    var d = new Date;
    console.log(60-d.getSeconds())
    return 60-d.getSeconds();
    }

    Timer {
        id: timer;
        interval: calcSecsToMin()*1000; running: true; repeat: true;
        onTriggered: clock.timeChanged()
    }

    Column {
        anchors.right: clock.right
        id: columnLayout
        Text {
            id: hoursText
            text: clock.hours
            width: clock.width
            color: clock.textColor
            font.pixelSize: clock.fontSize
            anchors.right: clock.right
            horizontalAlignment: Text.AlignRight
        }

        Text {
            id : dateText
            width: clock.width
            anchors.right: hoursText.right
            text: clock.date
            horizontalAlignment: Text.AlignRight
            color: parent.parent.textColor
            font.pixelSize: clock.fontSizeDate
            visible : clock.showDate
            Component.onCompleted: {timeChanged();}
        }
    }
}
