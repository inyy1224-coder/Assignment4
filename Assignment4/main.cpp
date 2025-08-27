#include <iostream>
#include <vector>
#include <string>

// PotionRecipe 클래스
class PotionRecipe {
public:
    std::string potionName;
    std::vector<std::string> ingredients;

    PotionRecipe(const std::string& name, const std::vector<std::string>& ingredients)
        : potionName(name), ingredients(ingredients) {}
};

// AlchemyWorkshop 클래스
class AlchemyWorkshop {
private:
    std::vector<PotionRecipe> recipes;

public:
    void addRecipe(const std::string& name, const std::vector<std::string>& ingredients) {
        recipes.push_back(PotionRecipe(name, ingredients));
        std::cout << ">> 새로운 레시피 '" << name << "'이(가) 추가되었습니다." << std::endl;
    }

    void displayAllRecipes() const {
        if (recipes.empty()) {
            std::cout << "아직 등록된 레시피가 없습니다." << std::endl;
            return;
        }

        std::cout << "\n--- [ 전체 레시피 목록 ] ---" << std::endl;
        for (size_t i = 0; i < recipes.size(); ++i) {
            std::cout << "- 물약 이름: " << recipes[i].potionName << std::endl;
            std::cout << "  > 필요 재료: ";
            for (size_t j = 0; j < recipes[i].ingredients.size(); ++j) {
                std::cout << recipes[i].ingredients[j];
                if (j < recipes[i].ingredients.size() - 1) {
                    std::cout << ", ";
                }
            }
            std::cout << std::endl;
        }
        std::cout << "---------------------------\n";
    }

    // [추가] 물약 이름으로 검색
    void searchByPotionName(const std::string& name) const {
        bool found = false;
        for (const auto& recipe : recipes) {
            if (recipe.potionName == name) {
                std::cout << "\n[검색 결과] '" << name << "' 레시피:" << std::endl;
                std::cout << "- 물약 이름: " << recipe.potionName << std::endl;
                std::cout << "  > 필요 재료: ";
                for (size_t j = 0; j < recipe.ingredients.size(); ++j) {
                    std::cout << recipe.ingredients[j];
                    if (j < recipe.ingredients.size() - 1) std::cout << ", ";
                }
                std::cout << std::endl;
                found = true;
                break; // 이름은 중복되지 않으므로 찾으면 종료
            }
        }
        if (!found) {
            std::cout << ">> '" << name << "' 이름의 물약 레시피를 찾을 수 없습니다." << std::endl;
        }
    }

    // [추가] 재료로 검색
    void searchByIngredient(const std::string& ingredient) const {
        bool found = false;
        std::cout << "\n[검색 결과] '" << ingredient << "'(이)가 포함된 레시피:" << std::endl;
        for (const auto& recipe : recipes) {
            for (const auto& ing : recipe.ingredients) {
                if (ing == ingredient) {
                    std::cout << "- 물약 이름: " << recipe.potionName << std::endl;
                    found = true;
                    break; // 이 레시피는 출력했으므로 다음 레시피로
                }
            }
        }
        if (!found) {
            std::cout << ">> '" << ingredient << "' 재료가 포함된 레시피가 없습니다." << std::endl;
        }
    }
};

int main() {
    AlchemyWorkshop myWorkshop;

    while (true) {
        std::cout << "\n⚗️ 연금술 공방 관리 시스템" << std::endl;
        std::cout << "1. 레시피 추가" << std::endl;
        std::cout << "2. 모든 레시피 출력" << std::endl;
        std::cout << "3. 물약 이름으로 검색" << std::endl;
        std::cout << "4. 재료로 검색" << std::endl;
        std::cout << "5. 종료" << std::endl;
        std::cout << "선택: ";

        int choice;
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cout << "잘못된 입력입니다. 숫자를 입력해주세요." << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        if (choice == 1) {
            std::string name;
            std::cout << "물약 이름: ";
            std::cin.ignore(10000, '\n');
            std::getline(std::cin, name);

            std::vector<std::string> ingredients_input;
            std::string ingredient;
            std::cout << "필요한 재료들을 입력하세요. (입력 완료 시 '끝' 입력)" << std::endl;

            while (true) {
                std::cout << "재료 입력: ";
                std::getline(std::cin, ingredient);
                if (ingredient == "끝") break;
                ingredients_input.push_back(ingredient);
            }

            if (!ingredients_input.empty()) {
                myWorkshop.addRecipe(name, ingredients_input);
            }
            else {
                std::cout << ">> 재료가 입력되지 않아 레시피 추가를 취소합니다." << std::endl;
            }

        }
        else if (choice == 2) {
            myWorkshop.displayAllRecipes();

        }
        else if (choice == 3) {
            std::string name;
            std::cout << "검색할 물약 이름: ";
            std::cin.ignore(10000, '\n');
            std::getline(std::cin, name);
            myWorkshop.searchByPotionName(name);

        }
        else if (choice == 4) {
            std::string ingredient;
            std::cout << "검색할 재료 이름: ";
            std::cin.ignore(10000, '\n');
            std::getline(std::cin, ingredient);
            myWorkshop.searchByIngredient(ingredient);

        }
        else if (choice == 5) {
            std::cout << "공방 문을 닫습니다..." << std::endl;
            break;

        }
        else {
            std::cout << "잘못된 선택입니다. 다시 시도하세요." << std::endl;
        }
    }

    return 0;
}