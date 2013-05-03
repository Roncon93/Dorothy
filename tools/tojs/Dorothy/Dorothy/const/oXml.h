#ifndef __DOROTHY_CONST_OXML_H__
#define __DOROTHY_CONST_OXML_H__

#include "Dorothy/const/oDefine.h"

NS_DOROTHY_BEGIN

struct oClipXml
{
	enum
	{
		Texture = 'A',//0
			//<a>
			File = 'A',
			//</a>

			Clip = 'B',//1
				//<a>
				Rect = 'A'
				//</a>
	};
};

struct oEffectXml
{
	enum
	{
		Dorothy = 'A',
		Effect = 'B',
		Type = 'C',
		File = 'J'
	};
};

struct oFrameXml
{
	enum
	{
		Texture = 'A',//0
			// <a>
			File = 'A',
			Duration = 'B',
			// </a>

			Clip = 'B',//1
				// <a>
				Rect = 'A',
				// </a>
	};
};

struct oModelXml
{
	enum
	{
		Dorothy = 'A',//0
			//<a>
			File = 'A',
			FaceRight = 'B',
			UseBatch = 'C',
			//</a>

			Sprite = 'B',//1
				//<a>
				Key = 'A',
				Visible = 'B',
				Opacity = 'C',
				Position = 'D',
				Scale = 'E',
				Rotation = 'F',
				Skew = 'G',
				Name = 'H',
				Clip = 'I',
				//</a>

				KeyAnimation = 'C',//2
					KeyFrame = 'D',//3
						//<a>
						Duration = 'A',
//		 				Visible = 'B',
//		 				Opacity = 'C',
//		 				Position = 'D',
//		 				Scale = 'E',
//		 				Rotation = 'F',
//		 				Skew = 'G',
						EaseOpacity = 'H',
						EasePos = 'I',
						EaseScale = 'J',
						EaseRotate = 'K',
						EaseSkew = 'L',
						//</a>

 				FrameAnimation = 'E',//4
					//<a>
//		 			File = 'A',
					Begin = 'B',
					End = 'C',
					//</a>

				Look = 'F',//5
					//<a>
//		 			Name = 'H',
					//</a>

			Sound = 'G',//6
 				Track = 'H',//7
					//<a>
//	 				File = 'A',
					Time = 'B',
					Index = 'C',
					//</a>

			LookName = 'I',//8
				//<a>
//				Index = 'C',
//				Name = 'H'
				//</a>

			AnimationName = 'J',//9
				//<a>
//				Index = 'C',
//				Name = 'H'
				//</a>
	};
};

struct oFaceXml
{
	enum
	{
		Str = 'A',
		Pos = 'B'
	};
};

NS_DOROTHY_END

#endif // __DOROTHY_CONST_OXML_H__