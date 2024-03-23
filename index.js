const gdi = require('./native/gdi.node')

console.log(gdi)

// const defaultConfig = {
//     title: 'GDI Window',
//     appId: 'NODE_GDI',
//     width: 600,
//     height: 400,
//     backgroundColor: [39, 40, 34],
//     frameless: false,
//     titleBarHeight: 0,
//     transparency: false,
//     transparentColor: [255, 0, 0],
//     alwaysOnTop: false,
//     persistPosition: true,
//     minWidth: 150,
//     minHeight: 150
// };

gdi.OpenWindow()

console.log('Done')

setInterval(mainLoop, 100)

setTimeout(() => {
    gdi.AddElement('id1', 1)
    console.log('added')
}, 4000)

setTimeout(() => {
    gdi.RemoveElement('id1')
    console.log('removed')
}, 10000)

function mainLoop() {
    gdi.ProcessMessages()

}