all:
	g++ gen_fs_keys.cpp largeClass/largeClass.cpp largeClass/largeNum.cpp -o gen_fs_keys
	g++ fs.cpp largeClass/largeClass.cpp largeClass/largeNum.cpp -o fs
