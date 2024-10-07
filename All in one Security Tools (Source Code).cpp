#include <stdio.h>          // Standard input/output library for functions like printf, scanf
#include <string.h>         // String manipulation functions like strcmp, strcpy
#include <time.h>           // Time-related functions for logging timestamps
#include <stdlib.h>         // Standard library functions for memory allocation, process control
#include <unistd.h>         // UNIX standard functions for sleep and usleep
#include <ctype.h>          // Character type functions like tolower
#include <errno.h>          // Error handling functions and errno variable

// ANSI Color Codes for terminal output (used to add colors and text styles)
#define RESET     "\033[0m"      // Resets all attributes
#define RED       "\033[0;31m"   // Red text
#define GREEN     "\033[0;32m"   // Green text
#define YELLOW    "\033[0;33m"   // Yellow text
#define BLUE      "\033[0;34m"   // Blue text
#define CYAN      "\033[0;36m"   // Cyan text
#define MAGENTA   "\033[0;35m"   // Magenta text
#define BOLD      "\033[1m"       // Bold text
#define UNDERLINE "\033[4m"       // Underlined text

// Define constants for login system and file paths
#define MAX_ATTEMPTS 3             // Maximum number of login attempts
#define LOCKOUT_TIME 10            // Lockout duration in seconds after max attempts
#define MAX_WORD_LENGTH 100        // Maximum length for password inputs
#define LOG_FILE "program_log.txt" // Log file for general actions
#define ERROR_LOG_FILE "error_log.txt" // Log file for errors
#define FEEDBACK_FILE "feedback.txt" // File to store user feedback
#define DICTIONARY_FILE "dictionary.txt" // Dictionary file for password cracking

// Function to load settings from file (Removed theme-related settings)
void load_settings() {
    // No settings to load since themes are removed
}

// Function to save settings to file (Removed theme-related settings)
void save_settings() {
    // No settings to save since themes are removed
}

// Function to log actions to a file (appends actions with timestamps)
void log_action(const char *action) {
    FILE *log_file = fopen(LOG_FILE, "a"); // Open log file in append mode
    if (log_file) {                         // Check if file opened successfully
        time_t current_time = time(NULL);   // Get current time
        // Remove the newline character from ctime output
        char *time_str = ctime(&current_time); // Convert time to string
        time_str[strcspn(time_str, "\n")] = 0; // Remove newline
        fprintf(log_file, "[%s] %s\n", time_str, action); // Write log entry
        fclose(log_file);                    // Close the log file
    }
}

// Function to log errors to a separate error log file (appends errors with timestamps)
void log_error(const char *error_message) {
    FILE *log_file = fopen(ERROR_LOG_FILE, "a"); // Open error log file in append mode
    if (log_file) {                                // Check if file opened successfully
        time_t current_time = time(NULL);          // Get current time
        char *time_str = ctime(&current_time);     // Convert time to string
        time_str[strcspn(time_str, "\n")] = 0;     // Remove newline
        fprintf(log_file, "[%s] ERROR: %s\n", time_str, error_message); // Write error entry
        fclose(log_file);                           // Close the error log file
    }
}

// Utility function to clear the terminal screen
void clear_screen() {
    printf("\033[2J\033[H"); // ANSI escape codes to clear screen and move cursor to home position
}

// Fixed color definitions for message types using previously defined ANSI codes
#define SUCCESS GREEN    // Success messages will be in green
#define ERROR RED        // Error messages will be in red
#define WARNING YELLOW   // Warning messages will be in yellow
#define INFO BLUE        // Informational messages will be in blue

// Function to display the introductory information with group and university details
void display_intro() {
    clear_screen(); // Clear the terminal screen
    // Print decorative lines and information with appropriate colors
    printf(GREEN "=====================================\n" RESET);
    printf(CYAN "University Name: " GREEN "Fast Nuces\n" RESET);
    printf(CYAN "Subject: " GREEN "Programming Fundamentals\n" RESET);
    printf(CYAN "Teacher Name: " GREEN "Noman Hanif\n" RESET);
    printf(GREEN "=====================================\n" RESET);
    printf(CYAN "Group Members:\n" RESET);
    printf(CYAN "Hasnain Memon   (24k-2001)\n" RESET);
    printf(CYAN "Muhammad Mutahir (24k-2005)\n" RESET);
    printf(GREEN "=====================================\n" RESET);
    printf("\n\nPress ENTER to continue...");
    getchar();  // Wait for user to press Enter
    log_action("Displayed intro"); // Log the action
}

// Function to display the ASCII art banner for the program
void display_banner() {
    printf("%s", GREEN); // Set text color to green
    printf("====================================================================================\n"); // Decorative line
    // ASCII art representing "AIOST"
    printf("                  _    _     _       ___ _   _    ___  _   _ _____                \n");
    printf("                 / \\  | |   | |     |_ _| \\ | |  / _ \\| \\ | | ____|               \n");
    printf("                / _ \\ | |   | |      | ||  \\| | | | | |  \\| |  _|                 \n");
    printf("               / ___ \\| |___| |___   | || |\\  | | |_| | |\\  | |___                \n");
    printf("     ____  ___/_/___\\_\\_____|_____|_|___|_|_\\_| _\\___/|_| \\_|_____|  _     ____   \n");
    printf("    / ___|| ____/ ___| | | |  _ \\|_ _|_   _\\ \\ / / |_   _/ _ \\ / _ \\| |   / ___|  \n");
    printf("    \\___ \\|  _|| |   | | | | |_) || |  | |  \\ V /    | || | | | | | | |   \\___ \\  \n");
    printf("     ___) | |__| |___| |_| |  _ < | |  | |   | |     | || |_| | |_| | |___ ___) | \n");
    printf("    |____/|_____\\____|\\___/|_| \\_\\___| |_|   |_|     |_| \\___/ \\___/|_____|____/   \n");
    printf("====================================================================================\n"); // Decorative line
    printf("%s", RESET); // Reset text attributes
}

// Function to display a progress bar in the terminal
void show_progress_bar(int percentage) {
    int width = 50; // Total width of the progress bar
    int pos = (percentage * width) / 100; // Calculate position of the progress
    printf("["); // Start of progress bar
    for (int i = 0; i < width; ++i) { // Loop to fill the progress bar
        if (i < pos) printf("=");      // Filled part
        else if (i == pos) printf(">"); // Current position
        else printf(" ");               // Unfilled part
    }
    printf("] %d%%\r", percentage); // End of progress bar with percentage
    fflush(stdout); // Flush the output buffer to display immediately
}

// Function to display a spinner animation in the terminal
void show_spinner() {
    const char spinner_chars[] = {'|', '/', '-', '\\'}; // Spinner characters
    static int spinner_index = 0; // Static index to keep track of spinner state
    printf("%c", spinner_chars[spinner_index]); // Display current spinner character
    fflush(stdout); // Flush the output buffer to display immediately
    spinner_index = (spinner_index + 1) % 4; // Update spinner index cyclically
}

// Confirmation prompt function to confirm critical actions
int confirm_action_prompt(const char *action) {
    char response[10]; // Buffer to store user response
    // Prompt the user with a warning message
    printf("%s%sWARNING%s: Are you sure you want to %s? (y/n): ", WARNING, BOLD, RESET, action);
    scanf("%s", response); // Read user input
    // Clear input buffer to remove any remaining characters
    while (getchar() != '\n');
    if (tolower(response[0]) == 'y') { // Check if response starts with 'y' or 'Y'
        return 1; // User confirmed
    }
    return 0; // User did not confirm
}

// Function to play a beep sound using ASCII Bell character
void play_beep() {
    printf("\a"); // ASCII Bell character
    fflush(stdout); // Flush the output buffer to ensure the beep is played
}

// Function to display the help section with instructions
void display_help() {
    clear_screen(); // Clear the terminal screen
    // Print the help header with informational color and bold text
    printf("%s%sHelp Section%s\n", INFO, BOLD, RESET);
    printf("=====================================\n"); // Decorative line
    // List of help instructions
    printf("1. Select a tool by entering its corresponding number.\n");
    printf("2. Follow the on-screen prompts to use the selected tool.\n");
    printf("3. For any issues, refer to the documentation or contact support.\n");
    printf("4. To exit the program, select the 'Exit' option from the main menu.\n");
    printf("=====================================\n"); // Decorative line
    printf("\nPress ENTER to return to the main menu...");
    getchar(); // Wait for user to press Enter
}

// Function to get a valid menu choice from the user with input validation
int get_valid_choice(int min, int max) {
    int choice; // Variable to store user's choice
    while (1) { // Infinite loop until a valid choice is entered
        printf("%sChoose an option (%d-%d): %s", CYAN, min, max, RESET); // Prompt the user
        if (scanf("%d", &choice) != 1) { // Read user input and check if it's an integer
            printf("%s%sERROR%s: Invalid input! Please enter a number.\n", ERROR, RESET); // Error message
            // Clear input buffer to remove invalid input
            while (getchar() != '\n');
            continue; // Continue the loop to prompt again
        }
        if (choice < min || choice > max) { // Check if choice is within valid range
            printf("%s%sERROR%s: Choice out of range! Please try again.\n", ERROR, RESET); // Error message
        } else {
            // Clear input buffer to remove any remaining characters
            while (getchar() != '\n');
            break; // Exit the loop if a valid choice is entered
        }
    }
    return choice; // Return the valid choice
}

// Function to get user input with a prompt and an optional example
void get_input(char *buffer, size_t size, const char *prompt, const char *example) {
    printf("%s%s: %s", INFO, prompt, RESET); // Print the prompt with informational color
    if (example != NULL) { // If an example is provided
        printf("(%s): ", example); // Print the example
    } else {
        printf(": "); // Otherwise, just print a colon
    }
    if (fgets(buffer, size, stdin) != NULL) { // Read user input safely
        buffer[strcspn(buffer, "\n")] = '\0'; // Remove the newline character from input
    } else {
        buffer[0] = '\0'; // Set buffer to empty string if input fails
    }
}

// Function to display a user-friendly exit message and collect feedback
void user_exit() {
    clear_screen(); // Clear the terminal screen
    // Print exit message with green color and bold text
    printf("%s%sThank you for using the program! Goodbye!%s\n", GREEN, BOLD, RESET);
    printf("Would you like to provide feedback? (y/n): "); // Prompt for feedback
    char response[10]; // Buffer to store user response
    scanf("%s", response); // Read user input
    // Clear input buffer to remove any remaining characters
    while (getchar() != '\n');
    if(tolower(response[0]) == 'y') { // Check if response starts with 'y' or 'Y'
        char feedback[512]; // Buffer to store user feedback
        // Get user feedback with a prompt and example
        get_input(feedback, sizeof(feedback), "Enter your feedback", "e.g., The program is very useful");
        FILE *fb = fopen(FEEDBACK_FILE, "a"); // Open feedback file in append mode
        if (fb) { // Check if file opened successfully
            time_t current_time = time(NULL); // Get current time
            char *time_str = ctime(&current_time); // Convert time to string
            time_str[strcspn(time_str, "\n")] = 0; // Remove newline
            fprintf(fb, "[%s] %s\n", time_str, feedback); // Write feedback with timestamp
            fclose(fb); // Close the feedback file
            // Print success message
            printf("%s%sSUCCESS%s: Thank you for your feedback!\n", GREEN, BOLD, RESET);
        } else { // If feedback file couldn't be opened
            printf("%s%sERROR%s: Unable to save feedback.\n", ERROR, BOLD, RESET); // Error message
            log_error("Failed to open feedback file."); // Log the error
        }
    }
    log_action("Program exited"); // Log the exit action
    exit(0); // Terminate the program
}

// Function to check if the entered password matches the correct password
int check_password(const char *input_password) {
    const char *correct_password = "password123"; // Define the correct password
    return strcmp(input_password, correct_password) == 0; // Return 1 if passwords match, else 0
}

// Function to display the login header
void display_header() {
    // Print decorative lines and welcome message with green color and bold text
    printf("%s%s====================================================\n", GREEN, BOLD);
    printf("         Welcome to the Secure Login System         \n");
    printf("====================================================%s\n", RESET);
}

// Function to display a successful login message with animated transition
void display_success() {
    clear_screen(); // Clear the terminal screen
    // Print decorative lines and welcome message with green color and bold text
    printf("%s%s====================================================\n", GREEN, BOLD);
    printf("              LOGIN SUCCESSFUL! WELCOME              \n");
    printf("====================================================%s\n", RESET);
    // Animated transition indicating session loading
    printf("%sINFO%s: Loading your session", INFO, RESET);
    for(int i =0; i <3; i++) { // Loop to display dots
        printf(".");
        fflush(stdout); // Flush the output buffer to display immediately
        usleep(500000); // 0.5 seconds delay
    }
    printf("\n"); // Newline after animation
    sleep(1); // Additional delay
    log_action("Login successful"); // Log the successful login
}

// Function to handle the login system with attempts and lockout mechanism
void login_system() {
    char password[100]; // Buffer to store user-entered password
    int attempts = 0;    // Counter for login attempts
    time_t lockout_start; // Variable to store lockout start time

    clear_screen(); // Clear the terminal screen
    display_header(); // Display the login header

    while (1) { // Infinite loop until successful login
        if (attempts >= MAX_ATTEMPTS) { // Check if max attempts exceeded
            time_t current_time = time(NULL); // Get current time
            int lockout_duration = (int)(current_time - lockout_start); // Calculate lockout duration

            if (lockout_duration < LOCKOUT_TIME) { // If still within lockout period
                printf("%s%sToo many failed attempts! You are locked out for %d seconds.%s\n", ERROR, BOLD, LOCKOUT_TIME - lockout_duration, RESET);
                sleep(1); // Wait for 1 second before next attempt
                continue; // Continue to the next iteration
            } else { // If lockout period has ended
                printf("%s%sLockout period is over. You can try again.%s\n", GREEN, BOLD, RESET);
                attempts = 0; // Reset the attempts counter
            }
        }

        // Prompt the user to enter the password
        get_input(password, sizeof(password), "Enter your password", "");

        if (check_password(password)) { // Check if password is correct
            display_success(); // Display success message
            break; // Exit the loop upon successful login
        } else { // If password is incorrect
            attempts++; // Increment the attempts counter
            play_beep(); // Play a beep sound as feedback
            // Inform the user about incorrect password and remaining attempts
            printf("%s%sWARNING%s: Incorrect password! You have %d attempt(s) remaining.\n", WARNING, BOLD, RESET, MAX_ATTEMPTS - attempts);
            if (attempts >= MAX_ATTEMPTS) { // If max attempts reached
                // Inform the user about lockout and set lockout start time
                printf("%s%sERROR%s: Too many failed attempts! Locking out for %d seconds...\n", ERROR, BOLD, RESET, LOCKOUT_TIME);
                lockout_start = time(NULL); // Record the start time of lockout
            }
        }
    }
}

// Tool 1: Simple Brute Force Attack Simulator
// Function to increment the password guess based on the given character set
int increment_password(char *password, int max_length, const char *charset, int charset_size) {
    int i = strlen(password) - 1; // Start from the last character of the current guess

    while (i >= 0) { // Loop until the first character
        int pos = strchr(charset, password[i]) - charset; // Find the position of current character in charset
        if (pos < charset_size - 1) { // If not the last character in charset
            password[i] = charset[pos + 1]; // Increment the character
            return 1; // Successful increment
        } else { // If it's the last character in charset
            password[i] = charset[0]; // Reset to first character
            i--; // Move to the previous character
        }
    }

    if (strlen(password) < max_length) { // If current guess length is less than max_length
        size_t len = strlen(password); // Get current length
        memset(password, charset[0], len); // Reset all characters to first charset character
        password[len] = charset[0]; // Add a new character
        password[len + 1] = '\0'; // Null-terminate the string
        return 1; // Successful increment
    }

    return 0; // Failed to increment (max length reached)
}

// Function to simulate a brute-force attack on a target password
void brute_force_simulator() {
    clear_screen(); // Clear the terminal screen
    printf("%s%sBrute Force Attack Simulator%s\n", CYAN, BOLD, RESET); // Print tool header with cyan color and bold text

    char target_password[100]; // Buffer to store the target password
    char charset[] = "abcdefghijklmnopqrstuvwxyz"; // Character set to use for guessing
    int charset_size = strlen(charset); // Size of the character set
    int max_length; // Maximum password length to attempt
    char guess[100] = ""; // Buffer to store the current guess
    int attempts = 0; // Counter for the number of attempts
    clock_t start_time, end_time; // Variables to store start and end times

    // Prompt the user to enter the target password and maximum length
    get_input(target_password, sizeof(target_password), "Enter the target password", "lowercase letters only");
    printf("%sEnter the maximum password length to attempt: %s", INFO, RESET);
    if (scanf("%d", &max_length) != 1 || max_length <=0 || max_length >= sizeof(guess)) { // Validate input
        printf("%s%sERROR%s: Invalid password length.\n", ERROR, BOLD, RESET); // Print error message
        // Clear input buffer to remove any remaining characters
        while (getchar() != '\n');
        printf("\nPress ENTER to return to menu...");
        getchar(); // Wait for user to press Enter
        return; // Exit the function due to invalid input
    }
    // Clear input buffer to remove any remaining characters
    while (getchar() != '\n');

    guess[0] = charset[0]; // Initialize the first character of the guess
    guess[1] = '\0'; // Null-terminate the guess string
    start_time = clock(); // Record the start time

    printf("%sINFO%s: Starting brute-force simulation...\n", INFO, RESET); // Inform the user
    sleep(1); // Wait for 1 second before starting

    while (1) { // Infinite loop to iterate through guesses
        attempts++; // Increment the attempts counter

        if (strcmp(guess, target_password) == 0) { // Check if the current guess matches the target password
            end_time = clock(); // Record the end time
            double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC; // Calculate time taken
            printf("\n%sSUCCESS%s: Password cracked: %s\n", GREEN, RESET, guess); // Inform success
            printf("%sSUCCESS%s: Total attempts: %d\n", GREEN, RESET, attempts); // Inform number of attempts
            printf("%sSUCCESS%s: Time taken: %.2f seconds\n", GREEN, RESET, time_taken); // Inform time taken
            log_action("Brute Force Attack Simulator executed"); // Log the action
            break; // Exit the loop upon success
        }

        if (!increment_password(guess, max_length, charset, charset_size)) { // Attempt to increment the guess
            printf("\n%sERROR%s: Failed to crack the password within the given parameters.\n", ERROR, RESET); // Inform failure
            log_action("Brute Force Attack Simulator failed to crack password"); // Log the failure
            break; // Exit the loop upon failure
        }

        // Show progress every 100,000 attempts
        if (attempts % 100000 == 0) {
            int percentage = (attempts / 1000000) * 10; // Example calculation for percentage
            if (percentage > 100) percentage = 100; // Cap the percentage at 100%
            show_progress_bar(percentage); // Display the progress bar
        }
    }
    printf("\nPress ENTER to return to menu...");
    getchar(); // Wait for user to press Enter
    log_action("Returned to main menu from Brute Force Simulator"); // Log the return action
}

// Tool 2: Basic File Encryption Tool (XOR Encryption)
void file_encryption_tool() {
    clear_screen(); // Clear the terminal screen
    printf("%s%sBasic File Encryption Tool%s\n", CYAN, BOLD, RESET); // Print tool header with cyan color and bold text

    char input_file[100], output_file[100], key[100]; // Buffers for filenames and encryption key
    FILE *infile, *outfile; // File pointers for input and output files
    unsigned char buffer; // Buffer to store file data
    int key_length, i = 0; // Variables for key length and iteration

    // Prompt the user to enter input file name, output file name, and encryption key
    get_input(input_file, sizeof(input_file), "Enter input file name", "e.g., input.txt");
    get_input(output_file, sizeof(output_file), "Enter output file name", "e.g., encrypted.bin");
    get_input(key, sizeof(key), "Enter encryption key", "e.g., mykey");

    key_length = strlen(key); // Calculate the length of the encryption key
    infile = fopen(input_file, "rb"); // Open the input file in binary read mode
    outfile = fopen(output_file, "wb"); // Open the output file in binary write mode

    if (!infile || !outfile) { // Check if files were opened successfully
        printf("%s%sERROR%s: Could not open files.\n", ERROR, BOLD, RESET); // Print error message
        log_error("File Encryption Tool: Failed to open files."); // Log the error
        printf("\nPress ENTER to return to menu...");
        getchar(); // Wait for user to press Enter
        return; // Exit the function due to error
    }

    printf("%sINFO%s: Encrypting file...\n", INFO, RESET); // Inform the user about encryption start
    show_progress_bar(20); // Display a progress bar at 20% completion
    while (fread(&buffer, 1, 1, infile)) { // Read one byte at a time from the input file
        buffer ^= key[i % key_length];  // XOR the byte with the key character
        fwrite(&buffer, 1, 1, outfile); // Write the encrypted byte to the output file
        i++; // Increment the counter
    }
    show_progress_bar(100); // Update the progress bar to 100% upon completion
    printf("\n%sSUCCESS%s: File encryption completed.\n", GREEN, RESET); // Inform the user about successful encryption

    fclose(infile); // Close the input file
    fclose(outfile); // Close the output file
    log_action("File Encryption Tool executed"); // Log the encryption action
    printf("\nPress ENTER to return to menu...");
    getchar(); // Wait for user to press Enter
}

// Tool 3: File Decryption Tool (XOR Decryption)
void file_decryption_tool() {
    clear_screen(); // Clear the terminal screen
    printf("%s%sBasic File Decryption Tool%s\n", CYAN, BOLD, RESET); // Print tool header with cyan color and bold text

    char input_file[100], output_file[100], key[100]; // Buffers for filenames and decryption key
    FILE *infile, *outfile; // File pointers for input and output files
    unsigned char buffer; // Buffer to store file data
    int key_length, i = 0; // Variables for key length and iteration

    // Prompt the user to enter encrypted file name, output file name, and decryption key
    get_input(input_file, sizeof(input_file), "Enter encrypted file name", "e.g., encrypted.bin");
    get_input(output_file, sizeof(output_file), "Enter output file name", "e.g., decrypted.txt");
    get_input(key, sizeof(key), "Enter decryption key", "e.g., mykey");

    key_length = strlen(key); // Calculate the length of the decryption key
    infile = fopen(input_file, "rb"); // Open the encrypted file in binary read mode
    outfile = fopen(output_file, "wb"); // Open the output file in binary write mode

    if (!infile || !outfile) { // Check if files were opened successfully
        printf("%s%sERROR%s: Could not open files.\n", ERROR, BOLD, RESET); // Print error message
        log_error("File Decryption Tool: Failed to open files."); // Log the error
        printf("\nPress ENTER to return to menu...");
        getchar(); // Wait for user to press Enter
        return; // Exit the function due to error
    }

    printf("%sINFO%s: Decrypting file...\n", INFO, RESET); // Inform the user about decryption start
    show_progress_bar(20); // Display a progress bar at 20% completion
    while (fread(&buffer, 1, 1, infile)) { // Read one byte at a time from the encrypted file
        buffer ^= key[i % key_length];  // XOR the byte with the key character to decrypt
        fwrite(&buffer, 1, 1, outfile); // Write the decrypted byte to the output file
        i++; // Increment the counter
    }
    show_progress_bar(100); // Update the progress bar to 100% upon completion
    printf("\n%sSUCCESS%s: File decryption completed.\n", GREEN, RESET); // Inform the user about successful decryption

    fclose(infile); // Close the encrypted file
    fclose(outfile); // Close the output file
    log_action("File Decryption Tool executed"); // Log the decryption action
    printf("\nPress ENTER to return to menu...");
    getchar(); // Wait for user to press Enter
}

// Tool 4: Dictionary Attack Tool
void dictionary_attack_tool() {
    clear_screen(); // Clear the terminal screen
    printf("%s%sDictionary Password Crack%s\n", CYAN, BOLD, RESET); // Print tool header with cyan color and bold text

    char enteredPassword[MAX_WORD_LENGTH]; // Buffer to store the password to crack
    char word[MAX_WORD_LENGTH]; // Buffer to store each word from the dictionary
    FILE *file; // File pointer for the dictionary file

    // Prompt the user to enter the password they want to crack
    get_input(enteredPassword, sizeof(enteredPassword), "Enter the password you want to crack", "e.g., password123");

    // Simulate loading process with spinner animation
    printf("%sINFO%s: Loading dictionary ", INFO, RESET); // Inform the user about loading
    for(int i =0; i <3; i++) { // Loop to display spinner
        show_spinner(); // Display spinner character
        usleep(300000); // 0.3 seconds delay
    }
    printf("\n"); // Newline after spinner

    // Open the dictionary file in read mode
    file = fopen(DICTIONARY_FILE, "r");
    if (file == NULL) { // Check if file opened successfully
        printf("%s%sERROR%s: Could not open dictionary file.\n", ERROR, BOLD, RESET); // Print error message
        log_error("Dictionary Attack Tool: Failed to open dictionary file."); // Log the error
        printf("\nPress ENTER to return to menu...");
        getchar(); // Wait for user to press Enter
        return; // Exit the function due to error
    }

    // Inform the user about the start of the search
    printf("%sINFO%s: Searching for the password...\n\n", INFO, RESET);
    sleep(1); // Simulate search time with a delay

    int found = 0; // Flag to indicate if password is found
    while (fgets(word, sizeof(word), file) != NULL) { // Read each word from the dictionary file
        word[strcspn(word, "\n")] = '\0'; // Remove newline character from the word

        if (strcmp(enteredPassword, word) == 0) { // Compare entered password with the current word
            printf("%sSUCCESS%s: Password found: %s\n", GREEN, RESET, word); // Inform the user of success
            found =1; // Set the found flag
            log_action("Dictionary Attack Tool: Password found"); // Log the success
            break; // Exit the loop upon finding the password
        }

        // Display each attempted word as a warning (for user excitement)
        printf("%sWARNING%s: Attempting: %s\r\n", WARNING, RESET, word);
        usleep(100000); // 0.1 seconds delay to simulate checking
    }

    if (!found) { // If password was not found in the dictionary
        printf("\n%sERROR%s: Password not found in the dictionary.\n", ERROR, RESET); // Inform the user
        log_action("Dictionary Attack Tool: Password not found"); // Log the failure
    }

    fclose(file); // Close the dictionary file
    printf("\nPress ENTER to return to menu...");
    getchar(); // Wait for user to press Enter
}

// Tool 5: Password Generator
void password_generator() {
    clear_screen(); // Clear the terminal screen
    printf("%s%sPassword Generator%s\n", CYAN, BOLD, RESET); // Print tool header with cyan color and bold text

    char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()"; // Character set for password generation
    int length, charset_size = strlen(charset); // Variables for password length and charset size
    char password[100]; // Buffer to store the generated password

    // Prompt the user to enter the desired password length
    printf("%sEnter the desired password length: %s", INFO, RESET);
    if (scanf("%d", &length) != 1 || length <=0 || length >= sizeof(password)) { // Validate input
        printf("%s%sERROR%s: Invalid password length.\n", ERROR, BOLD, RESET); // Print error message
        // Clear input buffer to remove any remaining characters
        while (getchar() != '\n');
        printf("\nPress ENTER to return to menu...");
        getchar(); // Wait for user to press Enter
        return; // Exit the function due to invalid input
    }
    // Clear input buffer to remove any remaining characters
    while (getchar() != '\n');

    srand(time(NULL)); // Seed the random number generator with current time
    for (int i = 0; i < length; i++) { // Loop to generate each character of the password
        password[i] = charset[rand() % charset_size]; // Select a random character from the charset
    }
    password[length] = '\0'; // Null-terminate the password string

    printf("%sSUCCESS%s: Generated password: %s\n", GREEN, RESET, password); // Inform the user of the generated password
    log_action("Password Generator executed"); // Log the action
    printf("\nPress ENTER to return to menu...");
    getchar(); // Wait for user to press Enter
}

// Tool 6: Password Strength Checker
void password_strength_checker() {
    clear_screen(); // Clear the terminal screen
    printf("%s%sPassword Strength Checker%s\n", CYAN, BOLD, RESET); // Print tool header with cyan color and bold text

    char password[100]; // Buffer to store the password to check
    int length, has_upper = 0, has_lower = 0, has_digit = 0, has_special = 0; // Variables to check password strength criteria

    // Prompt the user to enter the password to check
    get_input(password, sizeof(password), "Enter password to check strength", "e.g., P@ssw0rd!");

    length = strlen(password); // Calculate the length of the password
    for (int i = 0; i < length; i++) { // Loop through each character to check criteria
        if (isupper(password[i])) has_upper = 1; // Check for uppercase letters
        if (islower(password[i])) has_lower = 1; // Check for lowercase letters
        if (isdigit(password[i])) has_digit = 1; // Check for digits
        if (strchr("!@#$%^&*()", password[i])) has_special = 1; // Check for special characters
    }

    // Inform the user about the password strength
    printf("%sPassword Strength: %s", GREEN, RESET);
    if (length >= 8 && has_upper && has_lower && has_digit && has_special) // Check for strong password
        printf("%sStrong%s\n", GREEN, RESET);
    else if (length >= 6 && ((has_upper && has_lower) || (has_digit && has_special))) // Check for moderate password
        printf("%sModerate%s\n", YELLOW, RESET);
    else // Weak password
        printf("%sWeak%s\n", RED, RESET);

    log_action("Password Strength Checker executed"); // Log the action
    printf("\nPress ENTER to return to menu...");
    getchar(); // Wait for user to press Enter
}

// Tool 7: HexSecure - Secure Your Files with Signature-Based Detection
// Function to read a file and convert its contents to a hexadecimal string
char* read_file_as_hex(const char* filepath) {
    FILE *file = fopen(filepath, "rb"); // Open the file in binary read mode
    if (!file) { // Check if file opened successfully
        printf("%sERROR%s: Unable to open file %s\n", ERROR, RESET, filepath); // Print error message
        log_error("HexSecure: Failed to open file."); // Log the error
        return NULL; // Return NULL to indicate failure
    }

    fseek(file, 0, SEEK_END); // Move the file pointer to the end of the file
    long length = ftell(file); // Get the length of the file
    fseek(file, 0, SEEK_SET); // Move the file pointer back to the start

    char *buffer = (char*)malloc(length); // Allocate memory to read the file contents
    if (!buffer) { // Check if memory allocation was successful
        printf("%sERROR%s: Memory allocation failed.\n", ERROR, RESET); // Print error message
        log_error("HexSecure: Memory allocation failed."); // Log the error
        fclose(file); // Close the file
        return NULL; // Return NULL to indicate failure
    }

    if (fread(buffer, 1, length, file) != length) { // Read the file contents into the buffer
        printf("%sERROR%s: Failed to read file %s.\n", ERROR, RESET, filepath); // Print error message
        log_error("HexSecure: Failed to read file."); // Log the error
        free(buffer); // Free the allocated memory
        fclose(file); // Close the file
        return NULL; // Return NULL to indicate failure
    }
    fclose(file); // Close the file after reading

    // Allocate memory for the hexadecimal string (2 characters per byte + null terminator)
    char *hex_string = (char*)malloc(2 * length + 1);
    if (!hex_string) { // Check if memory allocation was successful
        printf("%sERROR%s: Memory allocation failed.\n", ERROR, RESET); // Print error message
        log_error("HexSecure: Memory allocation for hex string failed."); // Log the error
        free(buffer); // Free the original buffer memory
        return NULL; // Return NULL to indicate failure
    }

    // Convert each byte in the buffer to its hexadecimal representation
    for (long i = 0; i < length; i++) {
        sprintf(&hex_string[i * 2], "%02X", (unsigned char)buffer[i]);
    }
    hex_string[2 * length] = '\0'; // Null-terminate the hexadecimal string
    free(buffer); // Free the original buffer memory

    return hex_string; // Return the hexadecimal string
}

// Function to check if a hexadecimal string contains a given signature
int check_for_virus(const char* hex_string, const char* signature) {
    return (strstr(hex_string, signature) != NULL); // Return 1 if signature is found, else 0
}

// Function to scan a file for viruses based on a signature file
void scan_file(const char* filepath, const char* signature_file) {
    char *file_hex = read_file_as_hex(filepath); // Read the file as a hexadecimal string
    if (!file_hex) { // Check if reading was successful
        return; // Exit the function if failed
    }

    FILE *sig_file = fopen(signature_file, "r"); // Open the signature file in read mode
    if (!sig_file) { // Check if file opened successfully
        printf("%sERROR%s: Unable to open signature file %s\n", ERROR, RESET, signature_file); // Print error message
        log_error("HexSecure: Failed to open signature file."); // Log the error
        free(file_hex); // Free the allocated hexadecimal string
        return; // Exit the function due to error
    }

    char line[256]; // Buffer to store each line from the signature file
    int virus_found = 0; // Flag to indicate if a virus is found

    while (fgets(line, sizeof(line), sig_file)) { // Read each line from the signature file
        line[strcspn(line, "\n")] = 0; // Remove newline character from the line

        char *virus_name = strtok(line, ":"); // Extract the virus name
        char *signature = strtok(NULL, ":");  // Extract the virus signature
        if (!virus_name || !signature) continue; // Skip invalid lines

        // Remove spaces from the signature for accurate searching
        char clean_signature[256];
        int idx =0;
        for(int i=0; signature[i] != '\0' && idx <255; i++) {
            if(signature[i] != ' ') {
                clean_signature[idx++] = signature[i];
            }
        }
        clean_signature[idx] = '\0'; // Null-terminate the cleaned signature

        if (check_for_virus(file_hex, clean_signature)) { // Check if the file contains the signature
            printf("%sERROR%s: Virus detected: %s\n", ERROR, RESET, virus_name); // Inform the user about the detected virus
            virus_found = 1; // Set the virus_found flag
            log_action("HexSecure: Virus detected"); // Log the detection
            break; // Exit the loop upon finding a virus
        }
    }

    if (!virus_found) { // If no virus was found in the file
        printf("%sSUCCESS%s: No viruses found in the file.\n", GREEN, RESET); // Inform the user
        log_action("HexSecure: No viruses found"); // Log the successful scan
    }

    fclose(sig_file); // Close the signature file
    free(file_hex); // Free the allocated hexadecimal string
}

// Function to execute the HexSecure tool
void hexsecure() {
    clear_screen(); // Clear the terminal screen
    printf("%s%sHexSecure: Secure Your Files%s\n", CYAN, BOLD, RESET); // Print tool header with cyan color and bold text

    char file_to_scan[100], signature_file[100]; // Buffers for file to scan and signature file
    // Prompt the user to enter the file to scan and the signature file
    get_input(file_to_scan, sizeof(file_to_scan), "Enter the file to scan", "e.g., file.exe");
    get_input(signature_file, sizeof(signature_file), "Enter the signature file (database)", "e.g., signatures.txt");

    printf("%sINFO%s: Scanning file for viruses...\n", INFO, RESET); // Inform the user about scanning start
    scan_file(file_to_scan, signature_file); // Perform the virus scan

    log_action("HexSecure: Secure Your Files executed"); // Log the scan action
    printf("\nPress ENTER to return to menu...");
    getchar(); // Wait for user to press Enter
}

// Tool 8: Secure File Eraser (Shredder)
void secure_file_eraser() {
    clear_screen(); // Clear the terminal screen
    printf("%s%sSecure File Eraser (Shredder)%s\n", CYAN, BOLD, RESET); // Print tool header with cyan color and bold text

    char file_to_erase[100]; // Buffer to store the filename to erase
    // Prompt the user to enter the file to securely erase
    get_input(file_to_erase, sizeof(file_to_erase), "Enter the file to securely erase", "e.g., secret.txt");

    if (!confirm_action_prompt("erase the file")) { // Ask for user confirmation
        printf("%sINFO%s: Action canceled by the user.\n", INFO, RESET); // Inform the user about cancellation
        log_action("Secure File Eraser: Action canceled by user"); // Log the cancellation
        printf("\nPress ENTER to return to menu...");
        getchar(); // Wait for user to press Enter
        return; // Exit the function as action was canceled
    }

    FILE *file = fopen(file_to_erase, "wb"); // Open the file in binary write mode to overwrite
    if (!file) { // Check if file opened successfully
        printf("%sERROR%s: Unable to open file for erasing.\n", ERROR, RESET); // Print error message
        log_error("Secure File Eraser: Failed to open file for erasing."); // Log the error
        printf("\nPress ENTER to return to menu...");
        getchar(); // Wait for user to press Enter
        return; // Exit the function due to error
    }

    printf("%sINFO%s: Erasing file securely...\n", INFO, RESET); // Inform the user about the erasing process
    // Overwrite the file with random data multiple times to ensure it's securely erased
    for (int pass = 0; pass < 3; pass++) { // Perform 3 passes of overwriting
        // Simulate overwrite with a progress bar
        for(int i =0; i <=100; i +=20){
            show_progress_bar(i); // Display the progress bar
            usleep(200000); // 0.2 seconds delay between progress updates
        }
    }
    fclose(file); // Close the file after overwriting
    if (remove(file_to_erase) == 0) { // Attempt to delete the file
        printf("%sSUCCESS%s: File erased securely.\n", GREEN, RESET); // Inform the user of successful deletion
        log_action("Secure File Eraser: File erased securely"); // Log the successful deletion
    } else { // If file deletion failed
        printf("%sERROR%s: Failed to delete the file.\n", ERROR, RESET); // Inform the user of the failure
        log_error("Secure File Eraser: Failed to delete the file."); // Log the error
    }

    printf("\nPress ENTER to return to menu...");
    getchar(); // Wait for user to press Enter
}

// Tool 9: Binary File Creator (Virus Creator)
void binary_file_creator() {
    clear_screen(); // Clear the terminal screen
    printf("%s%sBinary File Creator (Virus Creator)%s\n", CYAN, BOLD, RESET); // Print tool header with cyan color and bold text

    FILE *file = fopen("testfile.exe", "wb"); // Create a binary file named "testfile.exe" in write mode

    if (!file) { // Check if file was created successfully
        printf("%s%sERROR%s: Unable to create file.\n", ERROR, BOLD, RESET); // Print error message
        log_error("Binary File Creator: Failed to create file."); // Log the error
        printf("\nPress ENTER to return to menu...");
        getchar(); // Wait for user to press Enter
        return; // Exit the function due to error
    }

    unsigned char virus_signature[] = { 0xBA, 0xDC, 0x0F, 0xFE, 0xE0, 0xDD, 0xF0, 0x0D }; // Define a mock virus signature

    fwrite(virus_signature, sizeof(virus_signature), 1, file); // Write the virus signature to the file
    fclose(file); // Close the file

    printf("%sSUCCESS%s: File 'testfile.exe' created successfully.\n", GREEN, RESET); // Inform the user of successful creation
    log_action("Binary File Creator: testfile.exe created"); // Log the creation action
    printf("\nPress ENTER to return to menu...");
    getchar(); // Wait for user to press Enter
}

// Function to display the tools menu with descriptions
void display_tools_menu() {
    clear_screen(); // Clear the terminal screen
    display_banner(); // Display the ASCII art banner
    // Removed display_recent_logs() as per user request
    printf("%s%sSelect a tool to use:                               Tool Description %s\n", CYAN, BOLD, RESET); // Print menu header with cyan color and bold text
    printf("=====================================\n"); // Decorative line
    // List of available tools with descriptions
    printf("%s1.%s  Brute Force Attack Simulator        - Simulate brute-force attacks on passwords\n", CYAN, RESET);
    printf("%s2.%s  Basic File Encryption Tool          - Encrypt files using XOR encryption\n", CYAN, RESET);
    printf("%s3.%s  Basic File Decryption Tool          - Decrypt files using XOR decryption\n", CYAN, RESET);
    printf("%s4.%s  Dictionary Attack Tool              - Attempt to crack passwords using a dictionary\n", CYAN, RESET);
    printf("%s5.%s  Password Generator                  - Generate strong random passwords\n", CYAN, RESET);
    printf("%s6.%s  Password Strength Checker           - Check the strength of your passwords\n", CYAN, RESET);
    printf("%s7.%s  HexSecure: Secure Your Files        - Scan files for known virus signatures\n", CYAN, RESET);
    printf("%s8.%s  Secure File Eraser (Shredder)       - Securely delete files beyond recovery\n", CYAN, RESET);
    printf("%s9.%s  Binary File Creator (Virus Creator) - Create a binary file with a virus signature\n", CYAN, RESET);
    printf("%s10.%s Help - View help instructions\n", CYAN, RESET);
    printf("%s11.%s Exit - Exit the program\n", CYAN, RESET);
    printf("=====================================\n"); // Decorative line
    printf("%s", RESET); // Reset text attributes
    log_action("Displayed tools menu"); // Log the menu display action
}

// Function to handle user selection and execute the corresponding tool
void handle_choice(int choice) {
    switch (choice) { // Switch-case to handle different tool selections
        case 1:
            brute_force_simulator(); // Execute Brute Force Attack Simulator
            break;
        case 2:
            file_encryption_tool(); // Execute Basic File Encryption Tool
            break;
        case 3:
            file_decryption_tool(); // Execute Basic File Decryption Tool
            break;
        case 4:
            dictionary_attack_tool(); // Execute Dictionary Attack Tool
            break;
        case 5:
            password_generator(); // Execute Password Generator
            break;
        case 6:
            password_strength_checker(); // Execute Password Strength Checker
            break;
        case 7:
            hexsecure(); // Execute HexSecure
            break;
        case 8:
            secure_file_eraser(); // Execute Secure File Eraser (Shredder)
            break;
        case 9:
            binary_file_creator(); // Execute Binary File Creator (Virus Creator)
            break;
        case 10:
            display_help(); // Display the help section
            break;
        case 11:
            user_exit(); // Exit the program
            break;
        default:
            // Handle invalid menu choices
            printf("%s%sERROR%s: Invalid choice! Please choose a valid tool.\n", ERROR, BOLD, RESET);
            log_action("Invalid tool choice"); // Log the invalid choice
            sleep(1); // Wait for 1 second before returning to menu
    }
}

// Main function: Entry point of the program
int main() {
    load_settings(); // Load settings (theme-related settings removed)

    display_intro(); // Display introductory information

    login_system(); // Handle user login

    // Infinite loop to continuously display the tools menu and handle user selections
    while (1) {
        display_tools_menu(); // Display the tools menu
        int choice = get_valid_choice(1, 11); // Get a valid choice from the user within the range 1-11
        handle_choice(choice); // Execute the corresponding tool based on user choice
    }

    return 0; // Return 0 to indicate successful program termination
}
