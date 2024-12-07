#include <string>
#include <vector>
#include <iostream>
#include <iomanip> // For std::fixed and std::setprecision
#include <cctype>  // For std::isalpha, std::isspace
#include <queue>
#include "Dish.hpp"
#include "Appetizer.hpp"
#include "Dessert.hpp"
#include "KitchenStation.hpp"
#include "MainCourse.hpp"
#include "StationManager.hpp"
#include "LinkedList.hpp"


// PREPARING DISH: Spaghetti Bolognese
// Pasta Station attempting to prepare Spaghetti Bolognese...
// Pasta Station: Insufficient ingredients. Replenishing ingredients...
// Pasta Station: Ingredients replenished.
// Pasta Station: Successfully prepared Spaghetti Bolognese.
// All dishes have been processed.

// PREPARING DISH: Vegan Salad
// Salad Station attempting to prepare Vegan Salad...
// Salad Station: Successfully prepared Vegan Salad.
// All dishes have been processed.

// PREPARING DISH: Seafood Paella
// Seafood Station attempting to prepare Seafood Paella...
// Seafood Station: Insufficient ingredients. Replenishing ingredients...
// Seafood Station: Unable to replenish ingredients. Failed to prepare Seafood Paella.
// Seafood Paella was not prepared.
// All dishes have been processed.

// PREPARING DISH: Grilled Chicken
// Grill Station attempting to prepare Grilled Chicken...
// Grill Station: Insufficient ingredients. Replenishing ingredients...
// Grill Station: Unable to replenish ingredients. Failed to prepare Grilled Chicken.
// Oven Station attempting to prepare Grilled Chicken...
// Oven Station: Successfully prepared Grilled Chicken.

// PREPARING DISH: Beef Wellington
// Grill Station attempting to prepare Beef Wellington...
// Grill Station: Dish not available. Moving to next station...
// Oven Station attempting to prepare Beef Wellington...
// Oven Station: Dish not available. Moving to next station...
// Pasta Station attempting to prepare Beef Wellington...
// Pasta Station: Dish not available. Moving to next station...
// Salad Station attempting to prepare Beef Wellington...
// Salad Station: Dish not available. Moving to next station...
// Beef Wellington was not prepared.
// All dishes have been processed.

int main()
{
    //Ingredient(const std::string& name, int quantity, int required_quantity, double price);
    Ingredient pasta("Pasta", 1, 2, 6.99);
    std::vector<Ingredient> pasta_ingr = {pasta};

    Ingredient salad("Salad", 2, 1, 3.99);
    std::vector<Ingredient> salad_ingr = {salad};

    Ingredient seafood("Seafood", 1, 2, 4.99);
    std::vector<Ingredient> seafood_ingr = {seafood};

    Ingredient grill("Grill", 2, 1, 4.99);
    std::vector<Ingredient> grill_ingr = {grill};

    Ingredient oven("Oven", 2, 1, 2.99);
    std::vector<Ingredient> oven_ingr = {oven};

//MainCourse(const std::string& name, const std::vector<Ingredient>& ingredients, const int &prep_time, const double &price, const CuisineType &cuisine_type, const CookingMethod &cooking_method, const std::string& protein_type, const std::vector<SideDish>& side_dishes, const bool &gluten_free);
    Dish* spaghetti_bol = new MainCourse("Spaghetti Bolognese", pasta_ingr, 1, 1.11, Dish::CuisineType::ITALIAN, MainCourse::CookingMethod::BOILED, "Beef", {}, true);
    Dish* veg_salad = new MainCourse("Vegan Salad", salad_ingr, 1, 1.11, Dish::CuisineType::ITALIAN, MainCourse::CookingMethod::BOILED, "Beef", {}, true);
    Dish* seafood_pae = new MainCourse("Seafood Paella", seafood_ingr, 1, 1.11, Dish::CuisineType::ITALIAN, MainCourse::CookingMethod::BOILED, "Beef", {}, true);
    Dish* grill_chicken = new MainCourse("Grilled Chicken", grill_ingr, 1, 1.11, Dish::CuisineType::ITALIAN, MainCourse::CookingMethod::BOILED, "Beef", {}, true);
    Dish* beef_well = new MainCourse("Beef Wellington", oven_ingr, 1, 1.11, Dish::CuisineType::ITALIAN, MainCourse::CookingMethod::BOILED, "Beef", {}, true);

    StationManager station_manager;
    KitchenStation* pasta_stat = new KitchenStation("Pasta Station");
    KitchenStation* salad_stat = new KitchenStation("Salad Station");
    KitchenStation* seafood_stat = new KitchenStation("Seafood Station");
    KitchenStation* grill_stat = new KitchenStation("Grill Station");
    KitchenStation* oven_stat = new KitchenStation("Oven Station");

/*
Can comment out test cases below
*/

    station_manager.addBackupIngredient(pasta);
    station_manager.addBackupIngredient(salad);
    station_manager.addBackupIngredient(oven);

    pasta_stat->replenishStationIngredients(pasta);
    salad_stat->replenishStationIngredients(salad);
    oven_stat->replenishStationIngredients(grill);

    station_manager.addStation(pasta_stat);
    station_manager.addStation(salad_stat);
    station_manager.addStation(seafood_stat);
    station_manager.addStation(grill_stat);
    station_manager.addStation(oven_stat);

    station_manager.assignDishToStation("Pasta Station", spaghetti_bol);
    station_manager.assignDishToStation("Salad Station", veg_salad);
    station_manager.assignDishToStation("Seafood Station", seafood_pae);
    station_manager.assignDishToStation("Grill Station", grill_chicken);
    station_manager.assignDishToStation("Oven Station", grill_chicken);

    station_manager.addDishToQueue(spaghetti_bol);
    station_manager.addDishToQueue(veg_salad);
    station_manager.addDishToQueue(seafood_pae);
    station_manager.addDishToQueue(grill_chicken);
    station_manager.addDishToQueue(beef_well);

    station_manager.processAllDishes();

    return 0;  
}
