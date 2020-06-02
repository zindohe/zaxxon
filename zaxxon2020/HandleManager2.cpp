#include "pch.h"
#include "HandleManager2.h"

#include "EntityManager.h"
#include "EntityFactory.h"

void HandleManager::HandlePlayerLaserMove(const float windowWidthSize)
{
    int count = 0;
        
   for (auto iterator = EntityManager::entities.begin(); iterator != EntityManager::entities.end(); iterator++ )
    {
        if ((*iterator)->type != EntityType::PlayerLaser)
        {
            continue;
        }
        sf::Vector2f position = (*iterator)->sprite.getPosition();
        position.x += 1;

        if (position.x > windowWidthSize)
        {
            (*iterator)->enabled = false;
            iterator--;
            EntityManager::entities.erase(iterator + 1);
            continue;
        }

        (*iterator)->sprite.setPosition(position);

    }
}

void HandleManager::HandleBackgrounfMovement(shared_ptr<Entity> background, const float windowWidthSize)
{

    sf::Vector2f postions = background->sprite.getPosition();
    postions.x--;
    background->sprite.setPosition(postions);

   if (postions.x + background->size.x < 0)
    {
        cout << "Size Before: " << EntityManager::entities.size() << endl;
        ChangeToNextStage();
        cout << "Size After : " << EntityManager::entities.size() << endl << endl;
    } 
  
}

void HandleManager::ChangeToNextStage()
{
    shared_ptr<Entity> backgroundToRemove = EntityManager::entities.at(0);
    shared_ptr<Entity> currentBackground = EntityManager::entities.at(1);
    EntityManager::entities.at(0) = currentBackground;

    float pos_x = currentBackground->sprite.getPosition().x + currentBackground->size.x;

    shared_ptr<Entity> nextBackground = nullptr;
    

    switch (currentBackground->type)
    {
        case EntityType::Stage1:
            nextBackground = EntityFactory::createEntity(EntityType::Stage2, sf::Vector2f(pos_x, 0.f), true);
            break;
        case EntityType::Stage2:
            nextBackground = EntityFactory::createEntity(EntityType::Stage3, sf::Vector2f(pos_x, 0.f), true);
            break;
        case EntityType::Stage3:
            nextBackground = EntityFactory::createEntity(EntityType::Stage4, sf::Vector2f(pos_x, 0.f), true);
            break;
        case EntityType::Stage4:
            nextBackground = EntityFactory::createEntity(EntityType::Stage5, sf::Vector2f(pos_x, 0.f), true);
            break;
        case EntityType::Stage5:
            nextBackground = EntityFactory::createEntity(EntityType::Stage6, sf::Vector2f(pos_x, 0.f), true);
            break;
        case EntityType::Stage6:
            nextBackground = EntityFactory::createEntity(EntityType::Stage7, sf::Vector2f(pos_x, 0.f), true);
            break;
        case EntityType::Stage7:
            nextBackground = EntityFactory::createEntity(EntityType::Stage8, sf::Vector2f(pos_x, 0.f), true);
            break;
        case EntityType::Stage8:
            nextBackground = EntityFactory::createEntity(EntityType::Stage9, sf::Vector2f(pos_x, 0.f), true);
            break;
        case EntityType::Stage9:
            nextBackground = EntityFactory::createEntity(EntityType::Stage1, sf::Vector2f(pos_x, 0.f), true);
            break;
    }
    
    EntityManager::entities.at(1) = nextBackground;
}
