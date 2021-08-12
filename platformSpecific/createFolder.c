void CreateDataFolderIfNotExists() { 
	sceIoMkdir(DATA_FOLDER, 0777);
}