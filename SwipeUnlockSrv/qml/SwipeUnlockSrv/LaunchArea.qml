import QtQuick 1.0

Rectangle {
    color: "blue"
    id:root
    width: parent.width
    height: row.height
    property int imgwidth:70;
    property int margin: parent.height+height
    property int curY: 0
    Row{
        spacing: (width-(root.imgwidth*r.model))/(r.model-1)
        width: parent.width
        id:row
        Repeater{
            id:r
            model: 5;
            delegate: Component{
                Image {
                    width: 70;
                    height: 70;
                    source: "image://icons/"+apps[index];
                    MouseArea{
                        id: m;
                        anchors.fill: parent
                        onClicked: {application.Hide(); application.Launch(apps[index]);}
                    }
                    Rectangle{
                        anchors.fill: parent;
                        visible: m.pressed;
                        color:"black"
                        opacity: 0.5
                    }
                }
            }
        }
    }
}
