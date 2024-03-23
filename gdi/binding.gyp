{
  "targets": [
    {
      "target_name": "gdi",
      "sources": [ "./index.cc" ],
      "libraries": [ "gdiplus.lib", "gdi32.lib"]
    },
    {
      "target_name": "action_after_build",
      "type": "none",
      "dependencies": [ "gdi" ],
      "copies": [
        {
          "files": [ "<(PRODUCT_DIR)/gdi.node" ],
          "destination": "../../native"
        }
      ]
    }
  ]
}