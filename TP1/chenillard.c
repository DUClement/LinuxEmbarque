#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define LED_PATH "/sys/class/leds/fpga_led%d/brightness"
#define LEDS 9

void chenillard(int ledNumber, char value) {
    char ledPath[50];
    int fd;
    snprintf(ledPath, sizeof(ledPath), LED_PATH, ledNumber);
    fd = open(ledPath, O_WRONLY);
    if (fd == -1) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    if (write(fd, &value, 1) == -1) {
        perror("Error writing file");
        close(fd);
        exit(EXIT_FAILURE);
    }
    close(fd);
}

int main()
 {
  while(1)
	{
        for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < LEDS; ++j) {
            chenillard(j + 1, '1');
            usleep(100000); 
        }
        for (int j = 0; j < LEDS; ++j) {
            chenillard(j + 1, '0');
            usleep(100000); 
        }
    }
}
    return 0;
}