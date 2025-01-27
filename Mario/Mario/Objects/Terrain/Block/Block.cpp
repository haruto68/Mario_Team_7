#include"Block.h"

Block::Block() :
	block_state(eBlockState::BRICK),
	content_state(eContentsState::DEFAULT),
	question_images(),
	brick_image(0),
	empty_image(0),
	question_num(0)
{

}

Block::~Block()
{

}

void Block::Initialize()
{
	//���\�[�X�Ǘ��C���X�^���X�擾
	ResourceManager* rm = ResourceManager::GetInstance();

	// �R���W�����ݒ�
	collision.is_blocking = true;
	collision.box_size = Vector2D(D_MONO, D_MONO);
	collision.object_type = eObjectType::eBlock;
	collision.hit_object_type.push_back(eObjectType::ePlayer);
	collision.hit_object_type.push_back(eObjectType::eEnemy);
	collision.hit_object_type.push_back(eObjectType::eGround);
	collision.hit_object_type.push_back(eObjectType::eItem);
	// �摜�ݒ�
	question_images = rm->GetImages("Resource/Images/Block/hatena.png", 4, 4, 1, 32, 32);
	brick_image = rm->GetImages("Resource/Images/Block/block.png")[0];
	empty_image = rm->GetImages("Resource/Images/Block/kara_block.png")[0];
	// ���C���[�ݒ�
	z_layer = 1;
	// �����ݒ�
	is_mobility = false;
}

void Block::Update(float delta_seconds)
{

}

void Block::Draw(const Vector2D& screen_offset) const
{
	// �I�t�Z�b�g�l����ɉ摜�̕`����s��
	Vector2D graph_location = this->location + screen_offset;

	switch (block_state)
	{
	case QUESTION:
		DrawRotaGraphF((int)graph_location.x, (int)graph_location.y, SIZE, 0.0, question_images[question_num], TRUE);
		break;
	case BRICK:
		DrawRotaGraphF((int)graph_location.x, (int)graph_location.y, SIZE, 0.0, brick_image, TRUE);
		break;
	case EMPTY:
		DrawRotaGraphF((int)graph_location.x, (int)graph_location.y, SIZE, 0.0, empty_image, TRUE);
		break;
	case HIDDEN:
		break;
	default:
		break;
	}

	//debug
	SetFontSize(24);
	switch (content_state)
	{
	case DEFAULT:
		DrawFormatString((int)graph_location.x, (int)graph_location.y, GetColor(255, 255, 255), "��");
		break;
	case COIN:
		DrawFormatString((int)graph_location.x, (int)graph_location.y, GetColor(255, 255, 0), "��");
		break;
	case COIN_10:
		DrawFormatString((int)graph_location.x, (int)graph_location.y, GetColor(255, 255, 0), "��");
		break;
	case RED:
		DrawFormatString((int)graph_location.x, (int)graph_location.y, GetColor(255, 0, 0), "��");
		break;
	case GREEN:
		DrawFormatString((int)graph_location.x, (int)graph_location.y, GetColor(0, 255, 0), "��");
		break;
	case STAR:
		DrawFormatString((int)graph_location.x, (int)graph_location.y, GetColor(255, 0, 0), "��");
		break;
	default:
		break;
	}
}

void Block::Finalize()
{

}

void Block::SetBlockState(eBlockState state)
{
	block_state = state;
}

void Block::SetContentsState(eContentsState state)
{
	content_state = state;
}