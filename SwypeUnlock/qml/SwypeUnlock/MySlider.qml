import QtQuick 1.0
import com.nokia.symbian 1.0
Column {
    id: root
    width: parent.width
    spacing: -15;
    property string min: "Min"
    property string max: "Max"
    property string title: "Text"
    property alias value: horslider.value;
    onTitleChanged: hortxt.text=root.title+": "+(horslider.value).toFixed(1);
    Text {
             id: hortxt
             text: root.title+": "+(horslider.value).toFixed(1);
             color: "white"
             font.pixelSize: 20
             anchors.left: parent.left
             anchors.leftMargin: 5
             anchors.right: parent.right
             horizontalAlignment: Text.AlignLeft
         }
         Slider {
             id: horslider
             width: root.width-(1*min.width/2)-max.width/2;
             x:min.width/2;
             //height: 70;
             orientation: Qt.Horizontal
             maximumValue: 0.9
             stepSize: 0.1
             minimumValue: 0.1
             value: 0.5
             onValueChanged: hortxt.text=root.title+": "+(horslider.value).toFixed(1);
         }
         Row{
             height: min.height+15
             anchors.horizontalCenter: root.horizontalCenter
             spacing: horslider.width-(1*min.width/2)-max.width/2-10
             Text {
                 id: min
                 color:"white"
                 text: root.min
                 font.pixelSize: 14;
             }
             Text {
                 id: max
                 color:"white"
                 text: root.max
                 font.pixelSize: 14
             }
         }


}
