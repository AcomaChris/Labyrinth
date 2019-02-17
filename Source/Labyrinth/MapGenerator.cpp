// Actor Class the provides functionality for generating a maze and returning basic tile data defining the maze

#include "MapGenerator.h"
#include "Engine/GameEngine.h"

// Sets default values
AMapGenerator::AMapGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMapGenerator::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMapGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMapGenerator::GenerateMap(int height, int width)
{
	for (int row = 0; row < height; row++) {
		Map.Add(FTile2DArray());
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Adding Tile2DArray Row"));
		}
		for (int column = 0; column < width; column++) {
			// Stick some bools in here until this is an algorithm
			Map[row].Add(FTile(false, true, false, false));
			if (GEngine) {
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Adding Tile"));
			}
		}
	}
}

