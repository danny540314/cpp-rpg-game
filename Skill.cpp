#include <iostream>
#include <string>

using namespace std;

class Skill {
private:
    string name;      // 技能名稱
    int damage;       // 技能傷害
    int mpCost;       // 魔力消耗

public:
    // 建構子：初始化技能的數值
    Skill(string n, int dmg, int mp) {
        name = n;
        damage = dmg;
        mpCost = mp;
    }

    // 使用技能的邏輯
    void use() {
        cout << "▶ 施放了專屬技能【" << name << "】！" << endl;
    }

    // 顯示技能資訊的邏輯
    void showInfo() {
        cout << "✨ 技能: " << name 
             << " | ⚔️ 傷害: " << damage 
             << " | 💧 消耗 MP: " << mpCost << endl;
    }

    // 取得技能傷害，要傳給 Player 拿去扣怪物的血
    int getDamage() {
        return damage;
    }

    // 其他必要的 Getter
    string getName() {
        return name;
    }

    int getMpCost() {
        return mpCost;
    }
};