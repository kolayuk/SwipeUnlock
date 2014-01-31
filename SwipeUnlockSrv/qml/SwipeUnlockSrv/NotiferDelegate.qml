import QtQuick 1.0

Item {
    visible: true
    id: itemContainer
    width: 360
    height: contentHeight();
    x:0;y:0;
    Rectangle{
        id:border;
        anchors.margins: {bottom:3;left:3;right:3;}
        anchors.fill:parent
        color: "black";
        opacity: 0.7
        radius: 3;
    }
    property int type: -1
    property alias itemSummary: summaryText.text
    property alias itemBody: contentText.text
    property alias timestamp: timestampText.text
    property alias typeIcon: notificationIcon.source

    function contentHeight() {
        return timestampText.y+timestampText.height+5;
    }

    Item {
        id: panelSize
        property int baseSize: itemContainer.width
        property int oneHalf: Math.round(baseSize/2)
        property int oneThird: Math.round(baseSize/3)
        property int oneFourth: Math.round(baseSize/4)
        property int oneSixth: Math.round(baseSize/6)
        property int oneEigth: Math.round(baseSize/8)
        property int oneTenth: Math.round(baseSize/10)
        property int oneTwentieth: Math.round(baseSize/20)
        property int oneTwentyFifth: Math.round(baseSize/25)
        property int oneThirtieth: Math.round(baseSize/30)
        property int oneSixtieth: Math.round(baseSize/60)
        property int oneEightieth: Math.round(baseSize/80)
        property int oneHundredth: Math.round(baseSize/100)
    }

    Image {
        id: notificationIcon
        source: icon
        anchors.top: parent.top
        anchors.topMargin: panelSize.oneThirtieth
        anchors.left: parent.left
        anchors.leftMargin: panelSize.oneThirtieth
        fillMode: Image.PreserveAspectFit
        asynchronous: true
    }
    Text {
        id: summaryText
        anchors.right: parent.right
        anchors.rightMargin: panelSize.oneThirtieth
        anchors.top: notificationIcon.top
        anchors.topMargin: 5;
        anchors.left: notificationIcon.right
        anchors.leftMargin: panelSize.oneThirtieth
        color: "white"
        font.bold: true
        font.pixelSize: 20
        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
        height: font.pixelSize+5;
        clip:true;
        elide: Text.ElideRight
        text: notifText
    }

    Text {
        id: contentText
        width: summaryText.width
        anchors.top: summaryText.top
        anchors.topMargin: Math.max(notificationIcon.height/3,5+summaryText.height);
        anchors.left: summaryText.left
        font.pixelSize: 15
        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
        height: font.pixelSize+5;
        clip:true;
        color: "white"
        text: from
    }

    Text {
        id: timestampText
        width: contentText.width
        anchors.top: notificationIcon.top
        anchors.topMargin: Math.max(notificationIcon.height*(2.0/3.0),10+summaryText.height+contentText.height);
        anchors.left: notificationIcon.right
        anchors.leftMargin: panelSize.oneThirtieth//notificationIcon.width/2
        anchors.bottomMargin: 20
        font.pixelSize: 15
        color:"white"
        wrapMode: Text.NoWrap
        elide: Text.ElideRight
        text:notifTime
    }
    MouseArea{
    anchors.fill: itemContainer
    onClicked: {notify.openViewer(index);}
    }
}
