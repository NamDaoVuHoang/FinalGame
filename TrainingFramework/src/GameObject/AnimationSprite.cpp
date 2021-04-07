#include "AnimationSprite.h"
#include "Shaders.h"
#include "Models.h"
#include "Camera.h"
#include "Texture.h"
#include "Hitbox.h"

extern GLint screenWidth;
extern GLint screenHeight;

AnimationSprite::AnimationSprite() {
}

AnimationSprite::~AnimationSprite() {
}

AnimationSprite::AnimationSprite(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture,
	int numFrames, float frameTimes) : m_numFrames(numFrames), m_currentTimes(0.0f), m_frameTimes(frameTimes), m_currentFrames(0) 
{
	m_pModel = model;
	m_pShader = shader;
	m_pCamera = nullptr;
	m_pTexture = texture;

	m_Vec3Position = Vector3(0, 0, 0);
	m_iHeight = 50;
	m_iWidth = 100;
	//m_Vec3Scale = Vector3((float)m_iWidth / screenWidth, (float)m_iHeight / screenHeight, 1);
}

AnimationSprite::AnimationSprite(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture,
	int numRows, int numFrames, int maxFrames, int currentRows, float frameTimes) : m_numRows(numRows), m_numFrames(numFrames), m_maxFrames(maxFrames), m_currentRows(currentRows), m_currentTimes(0.0f), m_frameTimes(frameTimes), m_currentFrames(0)
{

	for (int i = 0; i < m_numFrames; i++) {
		hitbox[i] = std::make_shared<Hitbox>(0.0f, 0.0f, 0.0f, 0.0f);
	}
	m_pModel = model;
	m_pShader = shader;
	m_pCamera = nullptr;
	m_pTexture = texture;

	m_Vec3Position = Vector3(0, 0, 0);
	m_iHeight = 50;
	m_iWidth = 100;
	//m_Vec3Scale = Vector3((float)m_iWidth / screenWidth, (float)m_iHeight / screenHeight, 1);
}

void AnimationSprite::Set2DPosition(GLfloat x, GLfloat y) {
	Sprite2D::Set2DPosition(x, y);
}

void AnimationSprite::Set2DPosition(Vector2 pos) {
	Sprite2D::Set2DPosition(pos);
}

void AnimationSprite::Draw()
{
	//printf("DONEDONE\n");
	glUseProgram(m_pShader->program);
	glBindBuffer(GL_ARRAY_BUFFER, m_pModel->GetVertexObject());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_pModel->GetIndiceObject());

	
	GLuint iTempShaderVaribleGLID = -1;
	Matrix matrixWVP;

	matrixWVP = m_WorldMat;//* m_pCamera->GetLookAtCamera();

	if (m_pTexture != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, m_pTexture->Get2DTextureAdd());
		if (m_pShader->iTextureLoc[0] != -1)
			glUniform1i(m_pShader->iTextureLoc[0], 0);
	}
	else
	{
		iTempShaderVaribleGLID = -1;
		iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"u_color");
		if (iTempShaderVaribleGLID != -1)
			glUniform4f(iTempShaderVaribleGLID, m_Color.x, m_Color.y, m_Color.z, m_Color.w);
	}


	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetAttribLocation((char*)"a_posL");
	if (iTempShaderVaribleGLID != -1)
	{
		glEnableVertexAttribArray(iTempShaderVaribleGLID);
		glVertexAttribPointer(iTempShaderVaribleGLID, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), VETEX_POSITION);
	}

	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetAttribLocation((char*)"a_uv");
	if (iTempShaderVaribleGLID != -1)
	{
		glEnableVertexAttribArray(iTempShaderVaribleGLID);
		glVertexAttribPointer(iTempShaderVaribleGLID, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), VETEX_UV);
	}

	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"u_alpha");
	if (iTempShaderVaribleGLID != -1)
		glUniform1f(iTempShaderVaribleGLID, 1.0);

	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"u_matMVP");
	if (iTempShaderVaribleGLID != -1)
		glUniformMatrix4fv(iTempShaderVaribleGLID, 1, GL_FALSE, matrixWVP.m[0]);

	
	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"numFrames");
	if (iTempShaderVaribleGLID != -1)
		glUniform1f(iTempShaderVaribleGLID, (float) m_numFrames);
	//printf("numFrames: %f\n", m_numFrames);

	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"currentFrames");
	if (iTempShaderVaribleGLID != -1)
		glUniform1f(iTempShaderVaribleGLID, (float) m_currentFrames);

	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"currentRows");
	if (iTempShaderVaribleGLID != -1)
		glUniform1f(iTempShaderVaribleGLID, (float) m_currentRows);

	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"numRows");
	if (iTempShaderVaribleGLID != -1)
		glUniform1f(iTempShaderVaribleGLID, (float) m_numRows);
	//printf("currentFrames: %f\n", m_currentFrames);

	glDrawElements(GL_TRIANGLES, m_pModel->GetNumIndiceObject(), GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

}


void AnimationSprite::Update(GLfloat deltatime) {
	m_currentTimes += deltatime;
	if (m_currentTimes >= m_frameTimes) {
		m_currentFrames++;
		//printf("%d",m_currentFrames);
		if (m_currentFrames >= m_maxFrames) {
			m_currentFrames = 0;
		}
		m_currentTimes = m_currentTimes - m_frameTimes;
	}
}

void AnimationSprite::UpdateStanding(GLfloat deltatime) {
	m_currentTimes += deltatime;
	if (m_currentTimes >= m_frameTimes) {
		m_currentFrames++;
		//printf("%d",m_currentFrames);
		if (m_currentFrames >= m_maxFrames) {
			m_currentFrames = 0;
		}
		m_currentTimes = m_currentTimes - m_frameTimes;
	}
}

void AnimationSprite::UpdateRunning(GLfloat deltatime, bool is_Running) {
	//printf("DONE");
	if (is_Running) {
		m_currentTimes += deltatime;
		if (m_currentTimes >= m_frameTimes) {
			m_currentFrames++;
			//printf("%d",m_currentFrames);
			if (m_currentFrames >= m_maxFrames) {
				m_currentFrames = 0;
			}
			m_currentTimes = m_currentTimes - m_frameTimes;
		}
	}
	else m_currentFrames = 0;
}

void AnimationSprite::UpdateAttacking(GLfloat deltatime, bool * is_Attacking) {
	if (is_Attacking) {
		m_currentTimes += deltatime;
		if (m_currentTimes >= m_frameTimes) {
			m_currentFrames++;
			//printf("%d",m_currentFrames);
			if (m_currentFrames >= m_maxFrames) {
				m_currentFrames = 0;
				*is_Attacking = false;
			}
			m_currentTimes = m_currentTimes - m_frameTimes;
		}
	}
	else m_currentFrames = 0;
	
}

void AnimationSprite::UpdateBlocking(GLfloat deltatime, bool is_Blocking) {
	if (is_Blocking) {
		m_currentTimes += deltatime;
		if (m_currentTimes >= m_frameTimes) {
			if (m_currentFrames < m_maxFrames-1) m_currentFrames++;
			m_currentTimes = m_currentTimes - m_frameTimes;
		}
	}
	else m_currentFrames = 0;
};

void AnimationSprite::UpdateTaunting(GLfloat deltatime, bool* is_Taunting) {
	if (is_Taunting) {
		m_currentTimes += deltatime;
		if (m_currentTimes >= m_frameTimes) {
			m_currentFrames++;
			//printf("%d",m_currentFrames);
			if (m_currentFrames >= m_maxFrames) {
				m_currentFrames = 0;
				*is_Taunting = false;
			}
			m_currentTimes = m_currentTimes - m_frameTimes;
		}
	}
	else m_currentFrames = 0;
}

void AnimationSprite::UpdateHealth(GLfloat deltatime) {
	if (m_currentFrames >= m_maxFrames - 1) return;
	m_currentTimes += deltatime;
	if (m_currentTimes >= m_frameTimes) {
		m_currentFrames++;
		//printf("%d",m_currentFrames);
		m_currentTimes = m_currentTimes - m_frameTimes;
	}
}

void AnimationSprite::UpdateDying(GLfloat deltatime) {
	if (m_currentFrames >= m_maxFrames - 1) return;
	m_currentTimes += deltatime;
	if (m_currentTimes >= m_frameTimes) {
		m_currentFrames++;
		//printf("%d",m_currentFrames);
		m_currentTimes = m_currentTimes - m_frameTimes;
	}
}

void AnimationSprite::UpdateFire(GLfloat deltatime) {
	m_currentTimes += deltatime;
	if (m_currentTimes >= m_frameTimes) {
		m_currentFrames++;
		//printf("%d",m_currentFrames);
		if (m_currentFrames >= m_maxFrames - 1) {
			m_currentFrames = 1;
		}
		m_currentTimes = m_currentTimes - m_frameTimes;
	}
};

void AnimationSprite::UpdateAttackingDemon(GLfloat deltatime) {
	m_currentTimes += deltatime;
	if (m_currentTimes >= m_frameTimes) {
		m_currentFrames++;
		//printf("%d",m_currentFrames);
		if (m_currentFrames >= m_maxFrames) {
			m_currentFrames = m_maxFrames - 2;
		}
		m_currentTimes = m_currentTimes - m_frameTimes;
	}
};

void AnimationSprite::SetCurrentFrames(int frame) {
	m_currentFrames = frame;
}

int AnimationSprite::GetCurrentFrame() {
	return m_currentFrames;
}

void AnimationSprite::SetHitboxX(GLfloat hitbox_x, int i) {
	hitbox[i]->setHitbox_x(hitbox_x);
};

void AnimationSprite::SetHitboxY(GLfloat hitbox_y, int i) {
	hitbox[i]->setHitbox_y(hitbox_y);
};

void AnimationSprite::SetCHitboxX(GLfloat c_hitbox_x, int i) {
	hitbox[i]->setCHitbox_x(c_hitbox_x);
};

void AnimationSprite::SetCHitboxY(GLfloat c_hitbox_y, int i) {
	hitbox[i]->setCHitbox_y(c_hitbox_y);
};

GLfloat AnimationSprite::getHitbox_x(int i) {
	return hitbox[i]->getHitbox_x();
};
GLfloat AnimationSprite::getHitbox_y(int i) {
	return hitbox[i]->getHitbox_y();
};
GLfloat AnimationSprite::getCHitbox_x(int i) {
	return hitbox[i]->getCHitbox_x();
};
GLfloat AnimationSprite::getCHitbox_y(int i) {
	return hitbox[i]->getCHitbox_y();
};

void AnimationSprite::SetDamage(float damage) {
	this->damage = damage;
}