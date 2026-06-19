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
// ==================== Monster Class 開始 ====================
class Monster {
private:
    std::string name;        // 怪物名稱
    int hp;                  // 怪物血量
    int maxHp;               // 最大血量
    int attackPower;         // 攻擊力
    int rewardGold;          // 擊敗後獲得金幣

public:
    // 建構子
    Monster(std::string name, int hp, int attackPower, int rewardGold) {
        this->name = name;
        this->hp = hp;
        this->maxHp = hp;
        this->attackPower = attackPower;
        this->rewardGold = rewardGold;
    }

    // 攻擊玩家
    void attack() {
        if (!isAlive()) return;
        std::cout << "👾 " << name << " 發動了攻擊，造成了 " << attackPower << " 點傷害！\n";
    }

    // 受到傷害
    void takeDamage(int damage) {
        if (damage < 0) damage = 0;
        hp -= damage;
        if (hp < 0) hp = 0;
        
        std::cout << "💥 " << name << " 受到了 " << damage << " 點傷害！";
        std::cout << " (剩餘 HP: " << hp << "/" << maxHp << ")\n";
        
        if (!isAlive()) {
            std::cout << "💀 " << name << " 被擊敗了！\n";
            std::cout << "💰 掉落了 " << rewardGold << " 枚金幣！\n";
        }
    }

    // 判斷怪物是否存活
    bool isAlive() const {
        return hp > 0;
    }

    // 顯示怪物資訊（依規格 showinfo 的 i 為小寫）
    void showInfo() const {
        std::cout << "============== 怪物資訊 ==============\n";
        std::cout << "名稱: " << name << (isAlive() ? " [存活]" : " [死亡]") << "\n";
        std::cout << "血量: " << hp << " / " << maxHp << "\n";
        std::cout << "攻擊力: " << attackPower << "\n";
        std::cout << "掉落金幣: " << rewardGold << "\n";
        std::cout << "=====================================\n";
    }

    // 標準 OOP 封裝所需的 Getter 與 Setter
    std::string getName() const { return name; }
    void setName(std::string name) { this->name = name; }
    int getHp() const { return hp; }
    void setHp(int hp) { this->hp = hp; }
    int getAttackPower() const { return attackPower; }
    void setAttackPower(int attackPower) { this->attackPower = attackPower; }
    int getRewardGold() const { return rewardGold; }
    void setRewardGold(int rewardGold) { this->rewardGold = rewardGold; }
};
// ==================== Monster Class 結束 ====================