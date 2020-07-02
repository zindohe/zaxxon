#include "pch.h"
#include "HandleManager2.h"

#include "EntityManager.h"
#include "EntityFactory.h"
#include "Spawner.h"

void HandleManager::HandlePlayerLaserMove(const float windowWidthSize)
{
    int count = 0;
        
   for (auto iterator = EntityManager::entities.begin(); iterator != EntityManager::entities.end(); iterator++ )
    {
        if ((*iterator)->type != EntityType::PlayerLaser &&
            (*iterator)->type != EntityType::PlayerSuperLaserDown &&
            (*iterator)->type != EntityType::PlayerSuperLaserUp)
        {
            continue;
        }
        sf::Vector2f position = (*iterator)->sprite.getPosition();
        if ((*iterator)->type == EntityType::PlayerLaser) {
            position.x += 1;
        }
        else if ((*iterator)->type != EntityType::PlayerSuperLaserDown) {
            position.x += 1;
            position.y -= 1;
        }
        else if ((*iterator)->type != EntityType::PlayerSuperLaserUp) {
            position.x += 1;
            position.y += 1;
        }

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

void HandleManager::HandleBackgroundMovement(shared_ptr<Entity> background, const sf::Vector2u mainWindowSize)
{
    sf::Vector2f positions = background->sprite.getPosition();
    positions.x -= 1;
    background->sprite.setPosition(positions);

   if (positions.x + background->size.x < 0)
    {
        cout << "Size Before: " << EntityManager::entities.size() << endl;
        ChangeToNextStage();
        SpawnEnnemies(mainWindowSize);
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

void HandleManager::SpawnEnnemies(const sf::Vector2u mainWindowSize)
{
    shared_ptr<Entity> currentStage = EntityManager::entities.at(0);

    switch (currentStage->type)
    {
        case EntityType::Stage1:
            EnnemiesStage1(mainWindowSize);
            break;
        case EntityType::Stage2:
            EnnemiesStage2(mainWindowSize);
            break;
        case EntityType::Stage3:
            EnnemiesStage3(mainWindowSize);
            break;
        case EntityType::Stage4:
            EnnemiesStage4(mainWindowSize);
            break;
        case EntityType::Stage5:
            EnnemiesStage5(mainWindowSize);
            break;
        case EntityType::Stage6:
            EnnemiesStage6(mainWindowSize);
            break;
        case EntityType::Stage7:
            EnnemiesStage7(mainWindowSize);
            break;
        case EntityType::Stage8:
            EnnemiesStage8(mainWindowSize);
            break;
        case EntityType::Stage9:
            EntityManager::DeleteAllEnnemies();
            EntityManager::deleteEnemyLaser();
            //EnnemiesStage9(mainWindowSize);
            break;
    }

}


void HandleManager::EnnemiesStage1(const sf::Vector2u mainWindowSize)
{

    EntityManager::DeleteAllEnnemies();
    
    //Ennemies Alpha
    
    Spawner::LinearStrategy(mainWindowSize, EntityType::EnnemyAlphaHorizontalLeft, 4, sf::Vector2f(700.f, 0.f));

}

void HandleManager::EnnemiesStage2(const sf::Vector2u mainWindowSize)
{
    EntityManager::DeleteAllEnnemies();

     //Ennemies Alpha

    Spawner::LinearStrategy(mainWindowSize, EntityType::EnnemyAlphaHorizontalLeft, 4, sf::Vector2f(700.f, 0.f));
    
    //Ennemies Beta

    Spawner::LinearStrategy(mainWindowSize, EntityType::EnnemyBetaHorizontalLeft, 2, sf::Vector2f(800.f, 0.f));

}

void HandleManager::EnnemiesStage3(const sf::Vector2u mainWindowSize)
{

    EntityManager::DeleteAllEnnemies();
   
    //Ennemies Alpha

    Spawner::LinearStrategy(mainWindowSize, EntityType::EnnemyAlphaHorizontalLeft, 8, sf::Vector2f(700.f, 0.f));


    //Ennemies Beta

    Spawner::LinearStrategy(mainWindowSize, EntityType::EnnemyBetaHorizontalLeft, 2, sf::Vector2f(800.f, 0.f));

}

void HandleManager::EnnemiesStage4(const sf::Vector2u mainWindowSize)
{

    EntityManager::DeleteAllEnnemies();

    //Ennemies Alpha

    Spawner::LinearStrategy(mainWindowSize, EntityType::EnnemyAlphaHorizontalLeft, 4, sf::Vector2f(700.f, 0.f));
    Spawner::LinearStrategy(mainWindowSize, EntityType::EnnemyAlphaHorizontalLeft, 4, sf::Vector2f(800.f, 50.f));


    //Ennemies Beta

    Spawner::LinearStrategy(mainWindowSize, EntityType::EnnemyBetaHorizontalLeft, 3, sf::Vector2f(900.f, 0.f));

}

void HandleManager::EnnemiesStage5(const sf::Vector2u mainWindowSize)
{

    EntityManager::DeleteAllEnnemies();

    //Ennemies Alpha

    Spawner::LinearStrategy(mainWindowSize, EntityType::EnnemyAlphaHorizontalLeft, 5, sf::Vector2f(700.f, 0.f));
    Spawner::LinearStrategy(mainWindowSize, EntityType::EnnemyAlphaHorizontalLeft, 5, sf::Vector2f(800.f, 50.f));


    //Ennemies Beta

    Spawner::LinearStrategy(mainWindowSize, EntityType::EnnemyBetaHorizontalLeft, 5, sf::Vector2f(900.f, 0.f));

}

void HandleManager::EnnemiesStage6(const sf::Vector2u mainWindowSize)
{

    EntityManager::DeleteAllEnnemies();

    //Ennemies Alpha

    Spawner::LinearStrategy(mainWindowSize, EntityType::EnnemyAlphaHorizontalLeft, 5, sf::Vector2f(700.f, 0.f));


    //Ennemies Beta

    Spawner::LinearStrategy(mainWindowSize, EntityType::EnnemyBetaHorizontalLeft, 4, sf::Vector2f(800.f, 50.f));
    Spawner::LinearStrategy(mainWindowSize, EntityType::EnnemyBetaHorizontalLeft, 4, sf::Vector2f(900.f, 0.f));

}


void HandleManager::EnnemiesStage7(const sf::Vector2u mainWindowSize)
{

    EntityManager::DeleteAllEnnemies();

    //Ennemies Alpha

    Spawner::LinearStrategy(mainWindowSize, EntityType::EnnemyAlphaHorizontalLeft, 4, sf::Vector2f(700.f, 0.f));


    //Ennemies Beta

    Spawner::LinearStrategy(mainWindowSize, EntityType::EnnemyBetaHorizontalLeft, 4, sf::Vector2f(800.f, 50.f));

    //Ennemies Boss

    Spawner::LinearStrategy(mainWindowSize, EntityType::EnnemyBoss, 1, sf::Vector2f(1000.f, 0.f));

}

void HandleManager::EnnemiesStage8(const sf::Vector2u mainWindowSize)
{

    EntityManager::DeleteAllEnnemies();

    //Ennemies Alpha

    Spawner::LinearStrategy(mainWindowSize, EntityType::EnnemyAlphaHorizontalLeft, 4, sf::Vector2f(700.f, 0.f));
    Spawner::LinearStrategy(mainWindowSize, EntityType::EnnemyAlphaHorizontalLeft, 4, sf::Vector2f(800.f, 50.f));


    //Ennemies Beta

    Spawner::LinearStrategy(mainWindowSize, EntityType::EnnemyBetaHorizontalLeft, 4, sf::Vector2f(900.f, 0.f));

    //Ennemies Boss

    Spawner::LinearStrategy(mainWindowSize, EntityType::EnnemyBoss, 2, sf::Vector2f(1000.f, 0.f));

}

void HandleManager::EnnemiesStage9(const sf::Vector2u mainWindowSize)
{

    cout << "EnnemiesStage3" << endl;

    EntityManager::DeleteAllEnnemies();

    //Ennemies Alpha

    Spawner::LinearStrategy(mainWindowSize, EntityType::EnnemyAlphaHorizontalLeft, 4, sf::Vector2f(700.f, 0.f));
    Spawner::LinearStrategy(mainWindowSize, EntityType::EnnemyAlphaHorizontalLeft, 4, sf::Vector2f(800.f, 50.f));


    //Ennemies Beta

    Spawner::LinearStrategy(mainWindowSize, EntityType::EnnemyBetaHorizontalLeft, 4, sf::Vector2f(900.f, 0.f));
    Spawner::LinearStrategy(mainWindowSize, EntityType::EnnemyBetaHorizontalLeft, 4, sf::Vector2f(1000.f, 50.f));

    //Ennemies Boss

    Spawner::LinearStrategy(mainWindowSize, EntityType::EnnemyBoss, 3, sf::Vector2f(1100.f, 0.f));

}
