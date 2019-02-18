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
	// Create our initial grid
	for (int row = 0; row < height; row++) {
		Map.Add(FTile2DArray());
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Adding Tile2DArray Row"));
		}
		for (int column = 0; column < width; column++) {
			Map[row].Add(FTile());
			if (GEngine) {
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Adding Tile"));
			}
		}
	}
	// Now that we have an initial grid, pick a random starting square and make the maze
	int startingRow = FMath::RandRange(0, height - 1);
	int startingColumn = FMath::RandRange(0, width - 1);
	RecursiveBacktrack(startingRow, startingColumn);
}

// Use a recursive backtracking algorithm to turn the Map into a maze
void AMapGenerator::RecursiveBacktrack(int row, int column) {
	FTile& thisTile = Map[row][column];
	thisTile.visited = true;

	TArray<Direction> options;
	options.Add(N);
	options.Add(S);
	options.Add(E);
	options.Add(W);

	// Consider each neighbour of this tile, in a random order
	while (options.Num() > 0) {
		Direction currentOption = options[FMath::RandRange(0, options.Num() - 1)];
		options.Remove(currentOption);
		int neighbourRow = row;
		int neighbourColumn = column;
		// Figure out based on the direction what neighbour tile we should look at, and early exit if the neighbour would be outside maze bounds
		switch (currentOption) {
		case N: 
			neighbourRow--;
			if (neighbourRow < 0)
				continue;
			break;
		case S:
			neighbourRow++;
			if (neighbourRow >= Map.Num())
				continue;
			break;
		case E:
			neighbourColumn++;
			if (neighbourColumn >= Map[row].Array.Num())
				continue;
			break;
		case W:
			neighbourColumn--;
			if (neighbourColumn < 0)
				continue;
			break;
		default:
			if (GEngine) {
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Unexpected direction in backtrack!"));
			}
			continue;
		}

		// Now we know we do have a neighbour within the maze, so check if it's already been visited (if so skip it)
		FTile& neighbourTile = Map[neighbourRow][neighbourColumn];
		if (neighbourTile.visited)
			continue;

		// We have an unvisited neighbour. Carve a path between our tile and it (remove our matching walls)
		switch (currentOption) {
		case N:
			thisTile.N = true;
			neighbourTile.S = true;
			break;
		case S:
			thisTile.S = true;
			neighbourTile.N = true;
			break;
		case E:
			thisTile.E = true;
			neighbourTile.W = true;
			break;
		case W:
			thisTile.W = true;
			neighbourTile.E = true;
			break;
		default:
			if (GEngine) {
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Unexpected direction in backtrack!"));
			}
		}
		// We've carved a path to this neighbour, so now recurse into this neighbour tile
		RecursiveBacktrack(neighbourRow, neighbourColumn);
	}
}

