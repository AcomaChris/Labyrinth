// Actor Class the provides functionality for generating a maze and returning basic tile data defining the maze

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MapGenerator.generated.h"

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

	// Constructor with wall info
	FTile(bool pN, bool pS, bool pE, bool pW)
	{
		N = pN;
		S = pS;
		E = pE;
		W = pW;
	}
	// Default constructor, all sides have walls
	FTile()
	{
		N = S = E = W = false;
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
	FTile operator[] (int32 i) {
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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
