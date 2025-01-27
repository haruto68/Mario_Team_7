#include"BackGround.h"

BackGround::BackGround() :
	back_ground_state(eBackGroundState::SKY),
	bushes_images(),
	mountain_images(),
	cloud_images(),
	sky_image(0),
	castle_image(0),
	image_num(0)
{

}

BackGround::~BackGround()
{

}

void BackGround::Initialize()
{
	//リソース管理インスタンス取得
	ResourceManager* rm = ResourceManager::GetInstance();

	// コリジョン設定
	collision.is_blocking = false;
	collision.object_type = eObjectType::eNone;
	// 画像設定
	bushes_images[0] = rm->GetImages("Resource/Images/ha0.png")[0];
	bushes_images[1] = rm->GetImages("Resource/Images/ha1.png")[0];
	bushes_images[2] = rm->GetImages("Resource/Images/ha2.png")[0];
	mountain_images[0] = rm->GetImages("Resource/Images/mountain_up.png")[0];
	mountain_images[1] = rm->GetImages("Resource/Images/mountain_left.png")[0];
	mountain_images[2] = rm->GetImages("Resource/Images/mountain_right.png")[0];
	mountain_images[3] = rm->GetImages("Resource/Images/mountain_surface.png")[0];
	mountain_images[4] = rm->GetImages("Resource/Images/mountain_surface1.png")[0];
	mountain_images[5] = rm->GetImages("Resource/Images/mountain_surface2.png")[0];
	cloud_images[0] = rm->GetImages("Resource/Images/cloud6.png")[0];
	cloud_images[1] = rm->GetImages("Resource/Images/cloud5.png")[0];
	cloud_images[2] = rm->GetImages("Resource/Images/cloud4.png")[0];
	cloud_images[3] = rm->GetImages("Resource/Images/cloud1.png")[0];
	cloud_images[4] = rm->GetImages("Resource/Images/cloud2.png")[0];
	cloud_images[5] = rm->GetImages("Resource/Images/cloud3.png")[0];
	sky_image= rm->GetImages("Resource/Images/sora.png")[0];
	castle_image = rm->GetImages("Resource/Images/siro1.png")[0];
	// レイヤー設定
	z_layer = 1;
	// 可動性設定
	is_mobility = false;
}

void BackGround::Update(float delta_seconds)
{

}

void BackGround::Draw(const Vector2D& screen_offset) const
{
	// オフセット値を基に画像の描画を行う
	Vector2D graph_location = this->location + screen_offset;
	switch (back_ground_state)
	{
	case BUSHES:
		DrawRotaGraphF(graph_location.x, graph_location.y, SIZE, 0.0, bushes_images[image_num], TRUE);
		break;
	case MOUNTAIN:
		DrawRotaGraphF(graph_location.x, graph_location.y, SIZE, 0.0, mountain_images[image_num], TRUE);
		break;
	case CLOUD:
		DrawRotaGraphF(graph_location.x, graph_location.y, SIZE, 0.0, cloud_images[image_num], TRUE);
		break;
	case SKY:
		DrawRotaGraphF(graph_location.x, graph_location.y, SIZE, 0.0, sky_image, TRUE);
		break;
	case CASTLE:
		DrawRotaGraphF(graph_location.x, graph_location.y, SIZE, 0.0, castle_image, TRUE);
		break;
	default:
		break;
	}
}

void BackGround::Finalize()
{

}

void BackGround::SetBackGroundState(eBackGroundState state)
{
	back_ground_state = state;
}

void BackGround::SetImageNum(int num)
{
	image_num = num;
}