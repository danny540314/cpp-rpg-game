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

    // 使用技能的邏輯 (修改為暗黑風格的文字)
    void use() {
        cout << "☠️ 你吟唱了古老的祈禱，施展出【" << name << "】！" << endl;
    }

    // 顯示技能資訊的邏輯 (修改為暗黑風格的排版與圖示)
    void showInfo() {
        cout << "📜 祈禱/戰技: " << name 
             << " | ⚔️ 殺傷: " << damage 
             << " | 🩸 燃燒理智 (MP): " << mpCost << endl;
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