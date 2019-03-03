// Actor Class the provides functionality for generating a maze and returning basic tile data defining the maze

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MapGenerator.generated.h"

// Readability enum for directions
// (and doing it this way we could expand to hex etc if we wanted)
enum Direction {
	N = 0,
	S = 1,
	E = 2,
	W = 3
};

// Blueprint-exposed Struct defining a basic map tile - 4 cardinal direction walls that are blocked or passable
USTRUCT(BlueprintType)
struct FTile
{
	GENERATED_BODY()

	// 4 bools defining each direction of the tile and where there is a wall or not
	// False = wall, True = pathway
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MapGeneration")
		bool N;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MapGeneration")
		bool S;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MapGeneration")
		bool E;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MapGeneration")
		bool W;

	// Bool used internally to keep track of when tiles have been visited by the maze generator algorithm
	bool visited;
	// Is this the escape tile? (simple game loop implementation for now)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MapGeneration")
	bool escape;

	// Constructor with wall info
	FTile(bool pN, bool pS, bool pE, bool pW)
	{
		N = pN;
		S = pS;
		E = pE;
		W = pW;
		visited = false;
		escape = false;
	}
	// Default constructor, all sides have walls
	FTile()
	{
		N = S = E = W = false;
		visited = false;
		escape = false;
	}
};

// Blueprint-accessible struct that lets us define a 2D array of Tiles.
// This is a work-around for UE4 not nicely letting you just have a 2D TArray
USTRUCT(BlueprintType)
struct FTile2DArray {
	GENERATED_BODY()

	// Our array of Tiles - basically the columns, and each Tile2DArray is a row
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MapGeneration")
	TArray<FTile> Array;

	// Override for the [] operator, which lets us use this struct like it really was just a 2D array
	// (Note that you can find this code online but they miss making it return a reference - we need a reference to we can modify the contents)
	FTile& operator[] (int32 i) {
		return Array[i];
	}

	void Add(FTile tile) {
		Array.Add(tile);
	}
};

UCLASS()
class LABYRINTH_API AMapGenerator : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMapGenerator();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MapGeneration")
		TArray<FTile2DArray> Map;

	UFUNCTION(BlueprintCallable, Category = "MapGeneration")
		void GenerateMap(int height, int width);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void RecursiveBacktrack(int row, int column);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool setEscape;
};
