mkdir build
cd build
cmake -DOPENCV_EXTRA_MODULES_PATH=../modules/opencv_contrib/modules -Dopencv_dnn_superres=ON .. -G "Visual Studio 17 2022"
