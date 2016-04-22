#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include "Camera.h"

void Camera::Init()
{
	//Angle initiale de la caméra
	m_yaw = 68.8214; // X
  	m_pitch = -0.3; // Y
 
 		//  X    Y    Z
  	SetPos(-25, 17, -40); //Position initiale de la caméra
}

void Camera::Refresh()
{
	// Paramètres pour rélger les coordonnées de la caméra (cos & sin pour gérer l'angle)
	m_lx = cos(m_yaw) * cos(m_pitch);
	m_ly = sin(m_pitch);
	m_lz = sin(m_yaw) * cos(m_pitch);

	m_strafe_lx = cos(m_yaw - M_PI_2);
	m_strafe_lz = sin(m_yaw - M_PI_2);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(m_x, m_y, m_z, m_x + m_lx, m_y + m_ly, m_z + m_lz, 0.0,1.0,0.0); //Caméra + vecteur de direction
}

	//Positionner la caméra (x, y, z)
void Camera::SetPos(float x, float y, float z)
{
	m_x = x;
	m_y = y;
	m_z =z;

	Refresh(); //Actualisation de la position
}

	//Obtenir la position de la caméra
void Camera::GetPos(float &x, float &y, float &z)
{
    x = m_x;
    y = m_y;
    z = m_z;
}

	//Obtenir les vecteurs de directions
void Camera::GetDirectionVector(float &x, float &y, float &z)
{
    x = m_lx;
    y = m_ly;
    z = m_lz;
}

	//Deplacement de la caméra (avancer / reculer)
void Camera::Move(float incr)
{
    float lx = cos(m_yaw)*cos(m_pitch);
    float ly = sin(m_pitch);
    float lz = sin(m_yaw)*cos(m_pitch);

    //Incrementation des axes pour avancer ou reculer (en fonction du nombre positif ou negatif)
	m_x = m_x + incr*lx;
	m_y = m_y + incr*ly;
	m_z = m_z + incr*lz;

	Refresh();
}


	//Deplacement latérals de la caméra (gauche / droite)
void Camera::Strafe(float incr)
{
	//Incrementation des axes pour aller à gauche ou à droite (en fonction du nombre positif ou negatif)
	m_x = m_x + incr*m_strafe_lx;
	m_z = m_z + incr*m_strafe_lz;

	Refresh();
}

	//Déplacements horizontals de la caméra (haut / bas)
void Camera::Fly(float incr)
{
	//Incrementation des axes pour monter ou descendre (en fonction du nombre positif ou negatif)
	m_y = m_y + incr;

	Refresh();
}

	//Pivoter l'angle x de la caméra
void Camera::RotateYaw(float angle)
{
	m_yaw += angle;

	Refresh();
}

	//Pivoter l'angle y de la caméra
void Camera::RotatePitch(float angle)
{
    const float limit = 89.0 * M_PI / 180.0;

	m_pitch += angle;

	//Ajout de limites pour que la caméra ne puisse pas aller au dessus de 90° en regardant en haut et en bas
    if(m_pitch < -limit)
        m_pitch = -limit;

    if(m_pitch > limit)
        m_pitch = limit;

	Refresh();
}

	//Définir l'angle sur X
void Camera::SetYaw(float angle)
{
	m_yaw = angle;

	Refresh();
}

	//Définir l'angle sur Y
void Camera::SetPitch(float angle)
{
    m_pitch = angle;

    Refresh();
}