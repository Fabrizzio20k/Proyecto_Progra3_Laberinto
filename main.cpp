#include "src/app.h"


int main() {
    std::cout << "moshi moshi" << std::endl;
    App *app = initApp();
    runApp(app);
    freeApp(&app);

    return 0;
}
