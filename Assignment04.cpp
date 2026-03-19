#include <iostream>
#include <vector>
#include <string>
#include <map>

// PotionRecipe 클래스: 재료 목록을 vector<string>으로 변경
class PotionRecipe {
public:
    std::string potionName;
    std::vector<std::string> ingredients; // 단일 재료에서 재료 '목록'으로 변경

    PotionRecipe() {}
    // 생성자: 재료 목록을 받아 초기화하도록 수정
    PotionRecipe(const std::string& name, const std::vector<std::string>& ingredients)
        : potionName(name), ingredients(ingredients) {
    }
};

// AlchemyWorkshop 클래스: 레시피 목록을 관리
class AlchemyWorkshop {
private:
    std::vector<PotionRecipe> recipes;

public:
    // addRecipe 메서드: 재료 목록(vector)을 매개변수로 받도록 수정
    void addRecipe(const std::string& name, const std::vector<std::string>& ingredients) {
        recipes.push_back(PotionRecipe(name, ingredients));
        std::cout << ">> 새로운 레시피 '" << name << "'이(가) 추가되었습니다." << std::endl;
    }

    // 모든 레시피 출력 메서드
    void displayAllRecipes() const {
        std::cout << "\n--- [ 전체 레시피 목록 ] ---" << std::endl;
        for (size_t i = 0; i < recipes.size(); ++i) {
            std::cout << "- 물약 이름: " << recipes[i].potionName << std::endl;
            std::cout << "  > 필요 재료: ";

            // 재료 목록을 순회하며 출력
            for (size_t j = 0; j < recipes[i].ingredients.size(); ++j) {
                std::cout << recipes[i].ingredients[j];
                // 마지막 재료가 아니면 쉼표로 구분
                if (j < recipes[i].ingredients.size() - 1) {
                    std::cout << ", ";
                }
            }
            std::cout << std::endl;
        }
        std::cout << "---------------------------";
    }

    bool checkAllRecipes() const {
        if (recipes.empty()) {
            std::cout << "아직 등록된 레시피가 없습니다." << std::endl;
            return true;
        }
        return false;
    }

    std::vector<PotionRecipe> getAllRecipes() const {
        return recipes;
    }

    PotionRecipe searchByName(const std::string& name) {
        for (int i = 0; i < recipes.size(); i++) {
            if (name == recipes[i].potionName) {
                return recipes[i];
            }
        }
        return PotionRecipe{};
    }

    std::vector<PotionRecipe> searchByIngredient(const std::string& ingredient) {
        std::vector<PotionRecipe> result;

        for (size_t i = 0; i < recipes.size(); i++) {
            for (size_t j = 0; j < recipes[i].ingredients.size(); j++) {
                if (ingredient == recipes[i].ingredients[j]) {
                    result.push_back(recipes[i]);
                    break;
                }
            }
        }

        return result;
    }

    std::vector<PotionRecipe> search(const std::string& keyword) {
        std::vector<PotionRecipe> result;

        for (size_t i = 0; i < recipes.size(); i++) {
            if (keyword == recipes[i].potionName) {
                result.push_back(recipes[i]);
            }
        }

        if (!result.empty())
            return result;

        for (size_t i = 0; i < recipes.size(); i++) {
            for (size_t j = 0; j < recipes[i].ingredients.size(); j++) {
                if (keyword == recipes[i].ingredients[j]) {
                    result.push_back(recipes[i]);
                    break;
                }
            }
        }

        return result;
    }
};

class StockManager
{
private:
    std::map<std::string, int> potionStock;
    const int MAX_STOCK = 3;

public:
    void initializeStock(const std::string& name)
    {
        potionStock[name] = MAX_STOCK;
        std::cout << ">> 새로운 레시피 '" << name << "'의 재고는 3개입니다." << std::endl;
    }

    bool dispensePotion(const std::string& name)
    {
        if (potionStock.find(name) == potionStock.end()) {
            std::cout << "등록되지 않은 물약입니다." << std::endl;
            return false;
        }
        if (potionStock[name] <= 0) {
            std::cout << name << "의 재고가 없습니다." << std::endl;
            return false;
        }
        potionStock[name]--;
        std::cout << name << " 지급 완료. 남은 재고: " << potionStock[name] << std::endl;
        return true;
    }

    void returnPotion(const std::string& name) {
        if (potionStock.find(name) == potionStock.end()) {
            std::cout << "등록되지 않은 물약입니다." << std::endl;
            return;
        }
        if (potionStock[name] >= MAX_STOCK) {
            std::cout << name << "의 재고가 이미 최대입니다." << std::endl;
            return;
        }
        potionStock[name]++;
        std::cout << name << " 반환 완료. 남은 재고: " << potionStock[name] << std::endl;
    }

    int getStock(const std::string& name)
    {
        if (potionStock.find(name) != potionStock.end()) {
            //std::cout << name << "의 재고 는 " << potionStock[name] << " 개입니다." << std::endl;
            return potionStock[name];
        }
        else {
            std::cout << "등록되지 않은 물약입니다." << std::endl;
            return -1;
        }
    }
};

int main() {
    AlchemyWorkshop myWorkshop;
    StockManager stockManager;

    while (true) {
        std::cout << "⚗️ 연금술 공방 관리 시스템" << std::endl;
        std::cout << "1. 레시피 추가" << std::endl;
        std::cout << "2. 모든 레시피 출력" << std::endl;
        std::cout << "3. 물약 이름으로 검색" << std::endl;
        std::cout << "4. 물약 재료로 검색" << std::endl;
        std::cout << "5. 물약 찾기 및 지급" << std::endl;
        std::cout << "6. 공병 반환" << std::endl;
        std::cout << "7. 종료" << std::endl;
        std::cout << "선택: ";

        int choice;
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cout << std::endl;
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

            // 여러 재료를 입력받기 위한 로직
            std::vector<std::string> ingredients_input;
            std::string ingredient;
            std::cout << "필요한 재료들을 입력하세요. (입력 완료 시 '끝' 입력)" << std::endl;

            while (true) {
                std::cout << "재료 입력: ";
                std::getline(std::cin, ingredient);

                // 사용자가 '끝'을 입력하면 재료 입력 종료
                if (ingredient == "끝") {
                    break;
                }
                ingredients_input.push_back(ingredient);
            }

            // 입력받은 재료가 하나 이상 있을 때만 레시피 추가
            if (!ingredients_input.empty()) {
                myWorkshop.addRecipe(name, ingredients_input);
                stockManager.initializeStock(name);
            }
            else {
                std::cout << ">> 재료가 입력되지 않아 레시피 추가를 취소합니다." << std::endl;
            }

        }
        else if (choice == 2) {
            if (myWorkshop.checkAllRecipes())
                continue;

            myWorkshop.displayAllRecipes();
            
            std::cout << "\n--- [ 재고 현황 ] ---" << std::endl;
            std::vector<PotionRecipe> all = myWorkshop.getAllRecipes();
            for (size_t i = 0; i < all.size(); i++) {
                std::cout << all[i].potionName << " 재고: " << stockManager.getStock(all[i].potionName) << std::endl;
            }
            std::cout << std::endl;
        }
        else if (choice == 3) {
            if (myWorkshop.checkAllRecipes())
                continue;

            std::string name;
            std::cout << "검색할 이름을 입력해주세요: ";
            std::cin.ignore(10000, '\n');
            std::getline(std::cin, name);

            PotionRecipe result = myWorkshop.searchByName(name);
            if (result.potionName.empty()) {
                std::cout << name << "으로 존재하는 레시피가 없습니다." << std::endl;
            }
            else
            {
                std::cout << name << "으로 등록된 레시피를 찾았습니다." << std::endl;
                std::cout << "  > 필요 재료: ";
                for (int j = 0; j < result.ingredients.size(); ++j) {
                    std::cout << result.ingredients[j];
                    if (j < result.ingredients.size() - 1) {
                        std::cout << ", ";
                    }
                }
            }
        }
        else if (choice == 4) {
            if (myWorkshop.checkAllRecipes())
                continue;

            std::string ingredient;
            std::cout << "검색할 재료를 입력해주세요: ";
            std::cin.ignore(10000, '\n');
            std::getline(std::cin, ingredient);

            std::vector<PotionRecipe> result = myWorkshop.searchByIngredient(ingredient);
            if (result.empty()) {
                std::cout << ingredient << "으로 존재하는 레시피가 없습니다." << std::endl;
            }
            else {
                for (size_t i = 0; i < result.size(); i++) {
                    std::cout << std::endl;
                    std::cout << ingredient << "을(를) 가진 포션 이름: " << result[i].potionName << std::endl;
                }
            }
        }
        else if (choice == 5) {
            if (myWorkshop.checkAllRecipes())
                continue;

            std::string keyword;
            std::cout << "검색할 물약의 이름 또는 재료를 입력해주세요: ";
            std::cin.ignore(10000, '\n');
            std::getline(std::cin, keyword);
            std::vector<PotionRecipe> result = myWorkshop.search(keyword);
            if (result.empty()) {
                std::cout << keyword << "에 해당하는 레시피가 없습니다." << std::endl;
            }
            else {
                for (size_t i = 0; i < result.size(); i++) {
                    std::cout << std::endl;
                    std::cout << i << ". 포션 이름: " << result[i].potionName << " 재고 현황: " << stockManager.getStock(result[i].potionName) << std::endl;
                }

                std::cout << "지급할 포션 번호를 입력해주세요: ";
                int index;
                std::cin >> index;

                if (std::cin.fail() || index < 0 || index >= (int)result.size()) {
                    std::cout << "잘못된 입력입니다." << std::endl;
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                }
                else {
                    stockManager.dispensePotion(result[index].potionName);
                }
            }
        }
        else if (choice == 6) {
            if (myWorkshop.checkAllRecipes())
                continue;

            std::string keyword;
            std::cout << "반환할 물약의 이름 또는 재료를 입력해주세요: ";
            std::cin.ignore(10000, '\n');
            std::getline(std::cin, keyword);
            std::vector<PotionRecipe> result = myWorkshop.search(keyword);
            if (result.empty()) {
                std::cout << keyword << "에 해당하는 레시피가 없습니다." << std::endl;
            }
            else {
                for (size_t i = 0; i < result.size(); i++) {
                    std::cout << i << ". 포션 이름: " << result[i].potionName << std::endl;
                }

                std::cout << "반환할 공병의 번호를 입력해주세요: ";
                int index;
                std::cin >> index;

                if (std::cin.fail() || index < 0 || index >= (int)result.size()) {
                    std::cout << "잘못된 입력입니다." << std::endl;
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                }
                else {
                    stockManager.returnPotion(result[index].potionName);
                }
            }
        }
        else if (choice == 7) {
            std::cout << "공방 문을 닫습니다..." << std::endl;
            break;
        }
        else {
            std::cout << "잘못된 선택입니다. 다시 시도하세요." << std::endl;
        }

        std::cout << std::endl;
    }

    return 0;
}