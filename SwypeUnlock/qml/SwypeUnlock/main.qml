import QtQuick 1.0
import com.nokia.symbian 1.0

Window {
    id: window
    MainPage{
        id: mainPage
        onAbout:{pgs.replace(aboutPage);}
    }
    AboutPage{
        id: aboutPage
        onBack:pgs.replace(mainPage);
    }

PageStack{
    id: pgs
    Component.onCompleted: pgs.push(mainPage);
    }

}


