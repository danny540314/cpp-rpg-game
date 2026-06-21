#include <iostream>
#include <string>
#include <vector>
#include <cstdlib> // 用於 system() 函數
using namespace std;

// ==================== Skill Class 開始 ====================
class Skill {
private:
    string name;      // 技能名稱
    int damage;       // 技能傷害
    int mpCost;       // 魔力消耗

public:
    Skill(string n, int dmg, int mp) {
        name = n;
        damage = dmg;
        mpCost = mp;
    }

    void use() {
        cout << "\n☠️ 你吟唱了古老的祈禱，施展出【" << name << "】！\n";
    }

    void showInfo() const {
        cout << "📜 祈禱/戰技: " << name
             << " | ⚔️ 殺傷: " << damage
             << " | 🩸 燃燒理智 (MP): " << mpCost << endl;
    }

    int getDamage() { return damage; }
    string getName() { return name; }
    int getMpCost() { return mpCost; }
};

// ==================== Monster Class 開始 ====================
class Monster {
private:
    string name;
    int hp;
    int maxHp;
    int attackPower;
    int rewardGold;

public:
    Monster(string name, int hp, int attackPower, int rewardGold) {
        this->name = name;
        this->hp = hp;
        this->maxHp = hp;
        this->attackPower = attackPower;
        this->rewardGold = rewardGold;
    }

    void attack() {
        if (!isAlive()) return;
        cout << "👾 【" << name << "】 發動了攻擊，造成了 " << attackPower << " 點傷害！\n";
    }

    void takeDamage(int damage) {
        if (damage < 0) damage = 0;
        hp -= damage;
        if (hp < 0) hp = 0;

        cout << "💥 【" << name << "】 受到了 " << damage << " 點傷害！";
        cout << " (剩餘 HP: " << hp << "/" << maxHp << ")\n";

        if (!isAlive()) {
            cout << "\n💀 【" << name << "】 被擊敗了！\n";
            cout << "💰 掉落了 " << rewardGold << " 枚金幣！\n";
        }
    }

    bool isAlive() const { return hp > 0; }

    void showInfo() const {
        cout << "============== 敵方資訊 ==============\n";
        cout << " 👁️ 魔物: " << name << "\n";
        cout << " 🩸 血量: " << hp << " / " << maxHp << "\n";
        cout << " ⚔️ 威脅: " << attackPower << "\n";
        cout << "======================================\n";
    }

    string getName() const { return name; }
    int getAttackPower() const { return attackPower; }
    int getRewardGold() const { return rewardGold; }
};

// ==================== Item Class 開始 ====================
enum class ItemType {
    HEAL_HP,
    HEAL_MP,
    BUFF_ATK
};

class Item {
private:
    string name;
    ItemType type;
    int effectValue;
    int quantity;

public:
    Item(string n, ItemType t, int effect, int q)
        : name(n), type(t), effectValue(effect), quantity(q) {}

    bool isAvailable() const { return quantity > 0; }

    void showInfo() const {
        cout << "【" << name << "】 ";
        cout << "剩餘數量: " << quantity << " | 效果: ";
        switch (type) {
            case ItemType::HEAL_HP: cout << "恢復 " << effectValue << " 點 HP"; break;
            case ItemType::HEAL_MP: cout << "恢復 " << effectValue << " 點 MP"; break;
            case ItemType::BUFF_ATK: cout << "永久提升 " << effectValue << " 點攻擊力"; break;
        }
        cout << endl;
    }

    int use() {
        if (isAvailable()) {
            quantity--;
            cout << "\n🧪 飲下了 [" << name << "]！\n";
            return effectValue;
        } else {
            cout << "\n❌ [" << name << "] 數量不足，無法使用！\n";
            return 0;
        }
    }

    void addQuantity(int q) { quantity += q; }
    ItemType getType() const { return type; }
    string getName() const { return name; }
};

// ==================== Player Class 開始 ====================
class Player {
private:
    string name;
    int hp, maxHp;
    int mp, maxMp;
    int attackPower;
    int gold;
    vector<Item> items;
    vector<Skill> skills;

public:
    Player(string n, int h, int m, int atk) {
        name = n;
        hp = h; maxHp = h;
        mp = m; maxMp = m;
        attackPower = atk;
        gold = 0;
    }

    void addItem(Item item) { items.push_back(item); }
    void addSkill(Skill skill) { skills.push_back(skill); }

    void takeDamage(int damage) {
        if (damage < 0) damage = 0;
        hp -= damage;
        if (hp < 0) hp = 0;
        cout << "🩸 【" << name << "】 受到了 " << damage << " 點的致命打擊！";
        cout << " (HP: " << hp << "/" << maxHp << ")\n";
    }

    void attack(Monster& m) {
        cout << "\n🗡️ 【" << name << "】 揮舞武器，向 " << m.getName() << " 發動攻擊！\n";
        m.takeDamage(attackPower);
    }

    void useSkill(int index, Monster& m) {
        if (index < 0 || index >= skills.size()) {
            cout << "\n❌ 無效的技能選擇\n";
            return;
        }
        Skill& selectedSkill = skills[index];
        if (mp >= selectedSkill.getMpCost()) {
            mp -= selectedSkill.getMpCost();
            selectedSkill.use();
            cout << "   (剩餘 MP: " << mp << "/" << maxMp << ")\n";
            m.takeDamage(selectedSkill.getDamage());
        } else {
            cout << "\n⚠️ MP不夠！無法施展【" << selectedSkill.getName() << "】！\n";
        }
    }

    void useItem(int index) {
        if (index < 0 || index >= items.size()) {
            cout << "\n❌ 無效的物品選擇\n";
            return;
        }
        Item& selectedItem = items[index];
        if (selectedItem.isAvailable()) {
            int effect = selectedItem.use();
            if (effect == 0) return; // 沒用到(數量不足)就不執行後續效果

            switch (selectedItem.getType()) {
                case ItemType::HEAL_HP:
                    hp += effect;
                    if (hp > maxHp) hp = maxHp;
                    cout << "❤️‍ HP 恢復至 " << hp << "/" << maxHp << "。\n";
                    break;
                case ItemType::HEAL_MP:
                    mp += effect;
                    if (mp > maxMp) mp = maxMp;
                    cout << "✨ MP 恢復至 " << mp << "/" << maxMp << "。\n";
                    break;
                case ItemType::BUFF_ATK:
                    attackPower += effect;
                    cout << "⚔️ 攻擊力提升至 " << attackPower << "！\n";
                    break;
            }
        }
    }

    void gainGold(int amount) {
        gold += amount;
        cout << "🪙 獲得了 " << amount << " 枚金幣，目前持有: " << gold << " 枚。\n";
    }

    bool spendGold(int amount) {
        if (gold >= amount) {
            gold -= amount;
            return true;
        }
        return false;
    }

    void restoreStatus() {
        hp = maxHp;
        mp = maxMp;
        cout << "\n🔥 你在營火旁坐下... 溫暖的火光驅散了黑暗。\n";
        cout << "✨ HP 與 MP 已完全恢復！\n";
    }

    void buyItem(ItemType type, int amount = 1) {
        for (auto& item : items) {
            if (item.getType() == type) {
                item.addQuantity(amount);
                return;
            }
        }
    }

    bool isAlive() const { return hp > 0; }

    void showStatus() const {
        cout << "======= 玩家狀態 =======\n";
        cout << " 👤 名稱: " << name << "\n";
        cout << " ❤️ HP:   " << hp << " / " << maxHp << "\n";
        cout << " 💧 MP:   " << mp << " / " << maxMp << "\n";
        cout << " ⚔️ 攻擊: " << attackPower << "\n";
        cout << " 💰 金幣: " << gold << "\n";
        cout << "========================\n\n";
    }

    void showSkills() const {
        cout << "\n--- 技能列表 ---\n";
        for (size_t i = 0; i < skills.size(); ++i) {
            cout << "【" << i + 1 << "】 ";
            skills[i].showInfo();
        }
    }

    void showItems() const {
        cout << "\n--- 背包中的物品 ---\n";
        for (size_t i = 0; i < items.size(); ++i) {
            cout << "【" << i + 1 << "】 ";
            items[i].showInfo();
        }
    }

    string getName() const { return name; }
    int getGold() const { return gold; }
};

// ==================== 遊戲系統與迴圈 ====================

// 戰鬥迴圈
void startCombat(Player& player, Monster& monster) {
    system("cls"); // 清空畫面
    cout << "\n⚠️ 遭遇了【" << monster.getName() << "】！\n";
    system("pause");

    while (player.isAlive() && monster.isAlive()) {
        system("cls"); // 每個回合開始前清空畫面，保持介面乾淨
        player.showStatus();
        monster.showInfo();

        cout << "\n================ 你的回合 ================\n";
        cout << "【1】 揮舞武器 (普通攻擊)\n";
        cout << "【2】 使用技能 (施展祈禱)\n";
        cout << "【3】 翻找背包 (使用物品)\n";
        cout << "==========================================\n";
        cout << "請選擇你的行動 (輸入數字): ";

        int choice;
        cin >> choice;

        // 玩家行動
        if (choice == 1) {
            player.attack(monster);
        }
        else if (choice == 2) {
            player.showSkills();
            cout << "請選擇要施展的技能 (輸入 0 取消): ";
            int skillChoice;
            cin >> skillChoice;
            if (skillChoice > 0) {
                player.useSkill(skillChoice - 1, monster);
            } else {
                continue; // 取消則重新選擇
            }
        }
        else if (choice == 3) {
            player.showItems();
            cout << "請選擇要使用的物品 (輸入 0 取消): ";
            int itemChoice;
            cin >> itemChoice;
            if (itemChoice > 0) {
                player.useItem(itemChoice - 1);
            } else {
                continue; // 取消則重新選擇
            }
        }
        else {
            cout << "\n❌ 無效的選擇，慌亂之中你浪費了一回合！\n";
        }

        // 怪物行動 (如果怪物還活著)
        if (monster.isAlive()) {
            cout << "\n================ 敵方回合 ================\n";
            monster.attack();
            player.takeDamage(monster.getAttackPower());
        }

        cout << "\n";
        system("pause"); // 暫停，讓玩家看清楚戰鬥結果
    }

    // 戰鬥結算
    system("cls");
    cout << "\n================ 戰鬥結束 ================\n";
    if (player.isAlive()) {
        cout << "🏆 勝利！\n";
        player.gainGold(monster.getRewardGold());
    } else {
        cout << "\n\n        【 Y O U   D I E D 】\n\n";
        cout << "    你的意識逐漸模糊，黑暗吞噬了一切...\n";
        cout << "    灰燼村最後的火光，熄滅了。\n\n";
    }
    system("pause");
}

// 營火商人系統
void visitMerchant(Player& player) {
    system("cls");
    cout << "\n🔥 你發現了隱蔽的營火，旁邊坐著一位穿著破布的神秘商人...\n";
    player.restoreStatus();
    system("pause");

    bool merchantAlive = true;
    while (merchantAlive && player.isAlive()) {
        system("cls");
        cout << "=============== 營火與商人 ===============\n";
        cout << " 💰 你的金幣: " << player.getGold() << " 枚\n";
        cout << "------------------------------------------\n";
        cout << "【1】 購買 [枯血藥劑] (15 金幣) - 恢復 50 HP\n";
        cout << "【2】 購買 [餘燼結晶] (20 金幣) - 恢復 30 MP\n";
        cout << "【3】 購買 [狂人骨灰] (25 金幣) - 永久提升 5 攻擊\n";
        cout << "【4】 🗡️ 攻擊商人 (後果自負)\n";
        cout << "【0】 🚶 離開營火，繼續旅途\n";
        cout << "==========================================\n";
        cout << "請選擇你要進行的交易: ";

        int choice;
        cin >> choice;

        if (choice == 1) {
            if (player.spendGold(15)) {
                player.buyItem(ItemType::HEAL_HP, 1);
                cout << "\n🎒 交易完成！獲得了 [枯血藥劑] x 1。\n";
            } else cout << "\n❌ 商人搖搖頭，你的金幣不夠。\n";
        }
        else if (choice == 2) {
            if (player.spendGold(20)) {
                player.buyItem(ItemType::HEAL_MP, 1);
                cout << "\n🎒 交易完成！獲得了 [餘燼結晶] x 1。\n";
            } else cout << "\n❌ 商人搖搖頭，你的金幣不夠。\n";
        }
        else if (choice == 3) {
            if (player.spendGold(25)) {
                player.buyItem(ItemType::BUFF_ATK, 1);
                cout << "\n🎒 交易完成！獲得了 [狂人骨灰] x 1。\n";
            } else cout << "\n❌ 商人搖搖頭，你的金幣不夠。\n";
        }
        else if (choice == 4) {
            cout << "\n商人的眼神突然變得無比銳利：「你會後悔的...」\n";
            system("pause");
            Monster secretBoss("深淵流浪者(商人)", 300, 15, 1000);
            startCombat(player, secretBoss);
            if (player.isAlive()) {
                system("cls");
                cout << "\n🩸 你殺死了商人！\n";
                player.buyItem(ItemType::HEAL_HP, 1);
                player.buyItem(ItemType::HEAL_MP, 1);
                player.buyItem(ItemType::BUFF_ATK, 1);
                cout << "✨ 搜刮屍體獲得了所有道具各 1 份。\n";
                merchantAlive = false;
                system("pause");
            } else {
                merchantAlive = false;
            }
        }
        else if (choice == 0) {
            cout << "\n🚶 你離開了營火，商人默默注視著你的背影。\n";
            system("pause");
            break;
        }
        else {
            cout << "\n❌ 商人疑惑地看著你...\n";
        }
        
        if (choice >= 1 && choice <= 3) system("pause");
    }
}

// ==================== 主程式 ====================
int main() {
    // 解決 Windows CMD 亂碼問題
    system("chcp 65001>nul"); 
    system("cls");

    // 印出遊戲標題
    cout << "====================================================\n";
    cout << "   ______           __                            \n";
    cout << "  / ____/  ____ _  / /_   ____   _____  _____     \n";
    cout << " / __/    / __ `/ / __ \\ / __ \\ / ___/ / ___/  \n";
    cout << "/ /___   / /_/ / / / / // /_/ // /    (__  )      \n";
    cout << "\\____/   \\__,_/ /_/ /_/ \\____//_/    /____/    \n";
    cout << "          深淵餘燼 Embers of the Abyss            \n";
    cout << "====================================================\n\n";
    cout << "  [ 在這個終年不見天日的村莊，你是最後的希望... ]\n\n";
    system("pause");

    // 初始化玩家 (強化版：120 HP, 60 MP, 18 ATK)
    Player player("見習守墓人", 120, 60, 18);
    
    // 初始化技能
    Skill shadowStrike("黯影打擊", 25, 10);
    Skill requiem("鎮魂輓歌", 50, 25);
    player.addSkill(shadowStrike);
    player.addSkill(requiem);
    
    // 初始化道具 (強化版補血量)
    Item hpPotion("枯血藥劑", ItemType::HEAL_HP, 50, 3);
    Item mpPotion("餘燼結晶", ItemType::HEAL_MP, 30, 2);
    Item atkBuff("狂人骨灰", ItemType::BUFF_ATK, 5, 1);
    player.addItem(hpPotion);
    player.addItem(mpPotion);
    player.addItem(atkBuff);
    
    // 初始化怪物 (難度調整)
    Monster zombie("腐朽活屍", 30, 5, 25);
    Monster gargoyle("黑棘石像鬼", 60, 12, 50);
    Monster boss("深淵領主", 150, 18, 500);

    // --- 遊戲流程開始 ---
    
    // 第一關
    startCombat(player, zombie);
    
    // 第二關
    if (player.isAlive()) {
        system("cls");
        cout << "\n樹林的深處傳來沉重的拍擊聲...\n";
        system("pause");
        startCombat(player, gargoyle);
    }
    
    // 休息區
    if (player.isAlive()) {
        visitMerchant(player);
    }
    
    // 最終 BOSS
    if (player.isAlive()) {
        system("cls");
        cout << "\n周圍的溫度急遽下降，純粹的黑暗壟罩了你...\n";
        cout << "最終的試煉降臨了！\n";
        system("pause");
        startCombat(player, boss);
    }
    
    // 結局
    if (player.isAlive()) {
        system("cls");
        cout << "\n====================================================\n";
        cout << "🎉 恭喜通關！\n\n";
        cout << "隨著深淵領主的倒下，一縷純粹的初火重新燃起。\n";
        cout << "你帶著火光回到了灰燼村，驅散了籠罩百年的黑暗。\n";
        cout << "泰南村... 不，灰燼村的傳奇，將永遠傳唱你的名字！\n";
        cout << "====================================================\n\n";
    }

    system("pause");
    return 0;
}
