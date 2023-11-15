
#include <stdio.h>

#define ORANGE 1
#define APPLE 2
#define Min_ALLOWED_LITERS 1
#define MAX_ALLOWED_LITERS 1000
#define ORANGE_JUICE_COST 0.2
#define APPLE_JUICE_COST 0.15
#define MACHINE_FLAT_RATE 5.0
#define YES 1
#define NO 2

typedef enum {
    FIVE_LITERS        = 5,
    TEN_LITERS         = 10,
    FIFTEEN_LITERS     = 15,
    TWENTY_LITERS      = 20,
    TWENTY_FIVE_LITERS = 25,
    NONE               = 0
} CanisterSize;

//-----------------------------------------------------------------------------
///
/// This function prompts the user to select a type of juice and the amount
/// of juice they want to fill. It then displays the available canister sizes
/// based on the selected juice type and prompts the user to choose a size.
/// Finally, it calculates and displays the filling costs.
///
/// @param juice_type Pointer to an integer where the selected juice type will be stored.
///                   Should be either ORANGE or APPLE.
/// @param liters_to_fill Pointer to an integer where the selected amount of juice to fill
///                       will be stored (between Min_ALLOWED_LITERS and MAX_ALLOWED_LITERS).
///
/// @return None
//
void getUserInput(int *juice_type, int *liters_to_fill) {

   while(1)
   {
      printf("\nWhich juice do you want to fill?\n1. Orange juice\n2. Apple juice\n > ");
      scanf("%i", juice_type);
      if (*juice_type == ORANGE || *juice_type == APPLE)
        {
          break;
        }
      else {
            printf("Invalid input! Please choose a valid juice.\n");
       }
   }

    while (1) {
        printf("\nHow many litres do you want to fill? (%d to %d)\n > ", Min_ALLOWED_LITERS, MAX_ALLOWED_LITERS);
        scanf("%i", liters_to_fill);

        if (*liters_to_fill >=  Min_ALLOWED_LITERS && *liters_to_fill <= MAX_ALLOWED_LITERS) {
            break;
        } else {
            printf("Invalid input! Please choose a valid amount.\n");
        }
    }
}
//-----------------------------------------------------------------------------
///
/// This function displays the available canister size options based on the selected juice type.
/// It prompts the user to choose a canister size for either orange or apple juice,
/// providing the available options and their corresponding liters.
///
/// @param juice_type The type of juice selected (ORANGE or APPLE).
///
/// @return None.
//
void displayCanisterOptions(int juice_type) {
    printf("\nWhich size of canister would you like to use for your %s juice?\n", (juice_type == ORANGE) ? "orange" : "apple");
    printf("- 5 litres\n- %s > ", (juice_type == ORANGE) ? "10 litres\n- 20 litres\n" : "15 litres\n- 25 litres\n");
}

//-----------------------------------------------------------------------------
///
/// This function calculates and returns the cost of a canister based on its size.
/// The cost is determined according to predefined rates for different canister sizes.
///
/// @param can_size The size of the canister for which the cost is calculated.
///                 Should be 5, 10, 15, or 20 for valid calculations.
///
/// @return The cost of the canister based on its size.
//
double getCanisterSizeCost(CanisterSize can_size) {
    switch (can_size) {
        case FIVE_LITERS       : return 0.10;
        case TEN_LITERS        : return 0.15;
        case FIFTEEN_LITERS    : return 0.20;
        case TWENTY_LITERS     : return 0.20;
        case TWENTY_FIVE_LITERS: return 0.25;
        default                : return 0.00;//shouldn't reach this point
    }
}
//-----------------------------------------------------------------------------
///
/// This function prompts the user to choose a canister size based on the selected juice type.
/// It displays the available canister size options and validates the user's input.
/// If the input is invalid, it prompts the user again until a valid option is chosen.
///
/// @param juice_type The type of juice selected (ORANGE or APPLE).
/// @param canister_size Pointer to the variable where the selected canister size will be stored.
///
/// @return None.
//
void getSelectedCanisterSize(int juice_type, int *canister_size) {
    displayCanisterOptions(juice_type);

    while (1) {
        scanf("%i", canister_size);

        if ((juice_type == ORANGE && (*canister_size == FIVE_LITERS || *canister_size == TEN_LITERS || *canister_size == TWENTY_LITERS)) ||
            (juice_type == APPLE && (*canister_size == FIVE_LITERS || *canister_size == FIFTEEN_LITERS || *canister_size == TWENTY_FIVE_LITERS))) {
            break; // Acceptable input
        } else {
            printf("Invalid input! Please choose a valid canister size.\n");
            displayCanisterOptions(juice_type);
        }
    }
}

//-----------------------------------------------------------------------------
///
/// This function calculates the filling cost based on the selected juice type, the
/// desired number of liters to fill, and the chosen canister size. It displays the
/// details of the filling process, including the number of canisters, left-over
/// liters, and the associated costs. The function also considers the flat rate
/// for using the machine.
///
/// @param juice_type The type of juice selected (ORANGE or APPLE).
/// @param liters_to_fill The desired number of liters to fill.
/// @param canister_size The selected canister size.
///
/// @return None.
//
void calculateFillingCost(int juice_type, int liters_to_fill, int canister_size) {
    int juice_amount, quantity;
    float can_cost, juice_cost;

    printf("\nIt is possible to fill %d canisters with the size of %i litres.\n", liters_to_fill / canister_size, canister_size);
    printf("This results in %i left-over litres.\n", liters_to_fill % canister_size);

    printf("\nThe filling costs are:\n");
    printf("----------------------------------------------\n");

    quantity = liters_to_fill / canister_size;
    juice_amount = quantity * canister_size;
    can_cost = quantity * getCanisterSizeCost(canister_size);

    juice_cost = (juice_type == ORANGE) ? ORANGE_JUICE_COST * juice_amount : APPLE_JUICE_COST * juice_amount;

    printf("- %i litres of %s juice: %.2f €\n", juice_amount, (juice_type == ORANGE) ? "orange" : "apple", juice_cost);
    printf("- %i canisters: %.2f €\n", quantity, can_cost);
    printf("- Flat rate for using the machine: %.2f €\n", MACHINE_FLAT_RATE);
    printf("----------------------------------------------\n");

    float total_cost = juice_cost + can_cost + MACHINE_FLAT_RATE;
    printf("This results in a total cost of %.2f €.\n", total_cost);
}

//-----------------------------------------------------------------------------
///
/// This function prompts the user for confirmation to proceed with filling the canisters.
/// It displays a menu with options to choose "Yes" or "No," and it ensures the user
/// provides a valid input. The function uses a pointer to update the confirmation status.
///
/// @param confirmation Pointer to an integer where the user's confirmation status will be stored.
///
/// @return None.
//
void getUserConfirmation(int *confirmation) {
    while (1) {
        printf("\nAre you sure you want to fill the canisters?\n1. Yes\n2. No\n > ");
        scanf("%i", confirmation);

        if (*confirmation == YES || *confirmation == NO) {
            break;
        } else {
            printf("Invalid input! Please choose a valid option.\n");
        }
    }
}

//-----------------------------------------------------------------------------
///
/// This function initiates the process of filling canisters. It collects user input
/// regarding the choice of juice, desired liters to fill, and the selected canister size.
/// Subsequently, it calculates and displays the filling costs. The process may be
/// repeated based on the user's confirmation.
///
/// @return None.
//
void startFillingProcess() {
    int juice_type, liters_to_fill, canister_size;

    getUserInput(&juice_type, &liters_to_fill);
    getSelectedCanisterSize(juice_type, &canister_size);
    calculateFillingCost(juice_type, liters_to_fill, canister_size);
}

//-----------------------------------------------------------------------------
///
/// This function manages user confirmation for filling canisters. It prompts the
/// user to confirm whether they want to proceed with the canister filling process.
/// If the user confirms (chooses 'Yes'), the filling process is initiated using
/// the startFillingProcess function. The process continues in a loop until the user
/// chooses not to proceed (selects 'No').
///
/// @return None.
//
void handleUserConfirmation() {
    int confirmation;
    getUserConfirmation(&confirmation);

    while (confirmation == NO) {
        startFillingProcess();
        getUserConfirmation(&confirmation);
    }
}

//-----------------------------------------------------------------------------
///
/// This is the main function of the juice filling machine calculator program.
/// It welcomes the user, initiates the canister filling process using the
/// startFillingProcess function, and manages user confirmation through the
/// handleUserConfirmation function. Once the user completes the filling process,
/// a closing message is displayed, indicating that the canisters will be filled
/// upon payment receipt. Finally, a thank you message is displayed for using
/// the juice filling machine calculator.
///
/// @return 0 on successful execution.
//
int main() {
    printf("Welcome to the juice filling machine calculator!\n");
    startFillingProcess();
    handleUserConfirmation();
    printf("\nThe canisters will be filled as soon as we receive your payment.\n");
    printf("Thank you for using the juice filling machine calculator!\n");

    return 0;
}
