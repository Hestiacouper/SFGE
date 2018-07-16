/*
 * transform.h
 *
 *  Created on: Feb 6, 2018
 *      Author: efarhan
 */

#ifndef SFGE_TRANSFORM_H_
#define SFGE_TRANSFORM_H_

#include <engine/entity.h>
#include <engine/component.h>
#include <SFML/System/Vector2.hpp>

namespace sfge
{


struct Transform2d
{
	sf::Vector2f Position = sf::Vector2f();
	sf::Vector2f Scale = sf::Vector2f(1.0f,1.0f);
	float EulerAngle = 0.0f;

};

class Transform2dManager : 
	public ComponentManager<Transform2d>, public Module
{
public:
	using Module::Module;
	void CreateComponent(json& componentJson, Entity entity) override;
	void DestroyComponent(Entity entity) override;

};

class TransformRequiredComponent
{
public:
	TransformRequiredComponent(Transform2d& transform);
protected:
	Transform2d & m_Transform;
};
}

#endif /* INCLUDE_ENGINE_TRANSFORM_H_ */
