#include "DxLib.h"
#include "ImgMng.h"

std::unique_ptr<ImgMng, ImgMng::ImgMngDeleter> ImgMng::s_Instance(new ImgMng());

ImgMng::ImgMng()
{
}

ImgMng::~ImgMng()
{
}
 const VEC_INT & ImgMng::GetID(std::string f_name)
 {
	 if (imgMap.find(f_name)==imgMap.end())	// f_nameの画像 IDのﾊﾝﾄﾞﾙがあるか？
	 {
		 imgMap[f_name].resize(1);	 //画像をﾘｻｲｽﾞする
		 imgMap[f_name][0] = LoadGraph(f_name.c_str(),true); //f_nameの画像IDを読み込み、ハンドルを作成する
	}
	 return imgMap[f_name]; //f_nameの画像IDのﾊﾝﾄﾞﾙを返す
 }

 const VEC_INT & ImgMng::GetID(std::string f_name, VECTOR2 diveSize, VECTOR2 divCnt, VECTOR2 chipOffset)
 {
	 if (imgMap.find(f_name) == imgMap.end())	// f_nameの画像 IDのﾊﾝﾄﾞﾙがあるか？
	 {
		 imgMap[f_name].resize(divCnt.x *divCnt.y);	 //画像をﾘｻｲｽﾞする
		 LoadDivGraph(f_name.c_str(), divCnt.x * divCnt.y, divCnt.x, divCnt.y,
		 diveSize.x, diveSize.y, &imgMap[f_name][0],true);//f_nameの画像IDを読み込み、ハンドルを作成する
	 }
	 return imgMap[f_name]; //f_nameの画像IDのﾊﾝﾄﾞﾙを返す
 }

 int ImgMng::Load(std::string fileName)
 {
	 if (imageData.find(fileName) == imageData.end()){ 
		imageData[fileName] = LoadGraph(fileName.c_str());
	}
	return imageData[fileName];
 }
