#!/bin/sh

cd build/Release/
zip -r MachoViewer MachoViewer.app
cd ../..
ruby "keys/sign_update.rb" build/Release/MachoViewer.zip keys/dsa_priv.pem
