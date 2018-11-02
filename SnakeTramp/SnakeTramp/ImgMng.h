#pragma once
#include <map>
#include <vector>
#include <mutex>
#include "VECTOR2.h"

using VEC_INT = std::vector<int>;  //VEC_INT ‚ðstd::vector<int>‚Æ‚µ‚Äˆµ‚¤ 

#define lpImgMng ImgMng::GetInstance()

class ImgMng
{
public:
	static ImgMng & GetInstance()
	{
		return *s_Instance;
	}
	const VEC_INT& GetID(std::string f_name);
	const VEC_INT& GetID(std::string f_name, VECTOR2 diveSize, VECTOR2 divCnt, VECTOR2 chipOffset);
private:
	struct ImgMngDeleter
	{
		void operator()(ImgMng *imgMng) const
		{
			delete imgMng;
		}
	};
	ImgMng();
	~ImgMng();

	static std::unique_ptr<ImgMng,ImgMngDeleter> s_Instance;

	std::map<std::string,VEC_INT> imgMap;	
};

