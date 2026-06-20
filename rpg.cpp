#include <iostream>
#include <string>
#include<vector>
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
    void showInfo() const {
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
//------Item Class start-----
enum class ItemType {
    HEAL_HP, // (對應：枯血藥劑)
    HEAL_MP, // (對應：餘燼結晶)
    BUFF_ATK // (對應：狂人骨灰)
};

class Item {
private:
    string name;
    ItemType type;
    int effectValue;
    int quantity;

public:
    Item(std::string n, ItemType t, int effect, int q)
        : name(n), type(t), effectValue(effect), quantity(q) {
    }


    bool isAvailable() const {
        return quantity > 0;
    }

    void showInfo() const {
        std::cout << "【" << name << "】 ";
        std::cout << "剩餘數量: " << quantity << " | 效果: ";

        switch (type) {
        case ItemType::HEAL_HP:
            std::cout << "恢復 " << effectValue << " 點 HP";
            break;
        case ItemType::HEAL_MP:
            std::cout << "恢復 " << effectValue << " 點 MP";
            break;
        case ItemType::BUFF_ATK:
            std::cout << "永久提升 " << effectValue << " 點攻擊力";
            break;
        }
        std::cout << std::endl;
    }


    int use() {
        if (isAvailable()) {
            quantity--;
            cout << "使用了 [" << name << "]！" << std::endl;
            return effectValue;
        }
        else {
            cout << name << " 數量不足，無法使用！" << std::endl;
            return 0;
        }
    }
    void addQuantity(int q) {
        quantity += q;
    }

    ItemType getType() const { return type; }
    string getName() const { return name; }
};
//-----Item Class finish-----
//player
class Player {
private:
    string name;           // 角色名稱
    int hp;                     // 角色目前血量
    int maxHp;                  // 最大血量
    int mp;                     // 角色目前魔力 (理智)
    int maxMp;                  // 最大魔力
    int attackPower;            // 攻擊力
    int gold;                   // 身上持有的金幣
    vector<Item> items;         // 背包裡的物品
    vector<Skill> skills;       // 學習到的祈禱/戰技

public:
    // constructor
    Player(string n, int h, int m, int atk) {
        name = n;
        hp = h;
        maxHp = h;
        mp = m;
        maxMp = m;
        attackPower = atk;
        gold = 0; // 初始金幣為 0
    }

    // 將物品加入背包
    void addItem(Item item) {
        items.push_back(item);
    }

    // 學習新技能
    void addSkill(Skill skill) {
        skills.push_back(skill);
    }

    // 受到傷害
    void takeDamage(int damage) {
        if (damage < 0) damage = 0;
        hp -= damage;
        if (hp < 0) hp = 0;

        cout << "🩸 【" << name << "】 受到了 " << damage << " 點的致命打擊！";
        cout << " (HP: " << hp << "/" << maxHp << ")\n";
    }

    // 普通攻擊
    void attack(Monster& m) {
        cout << "🗡️ 【" << name << "】 揮舞武器，向 " << m.getName() << " 發動攻擊！\n";
        m.takeDamage(attackPower); // 呼叫怪物的扣血邏輯
    }

    // 使用技能
    void useSkill(int index, Monster& m) {
        if (index < 0 || index >= skills.size()) {
            cout << "❌ 無效的技能選擇\n";
            return;
        }

        Skill& selectedSkill = skills[index];

        if (mp >= selectedSkill.getMpCost()) {
            mp -= selectedSkill.getMpCost();
            selectedSkill.use(); // 印出技能施展文字
            cout << "   (剩餘 MP: " << mp << "/" << maxMp << ")\n";
            m.takeDamage(selectedSkill.getDamage()); // 對怪物造成傷害
        }
        else {
            cout << "⚠️ MP不夠！無法施展【" << selectedSkill.getName() << "】！\n";
        }
    }

    // 使用物品
    void useItem(int index) {
        if (index < 0 || index >= items.size()) {
            cout << "❌無效的物品選擇\n";
            return;
        }

        Item& selectedItem = items[index];

        if (selectedItem.isAvailable()) {
            int effect = selectedItem.use(); // 呼叫 Item 的 use() 會扣除數量並印出名稱

            // 根據物品的 Enum 類型來決定效果
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

    // gold
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
        cout << "✨ 火源回復了生命！\n";
    }
    //購買
    void buyItem(ItemType type, int amount = 1) {
        for (auto& item : items) {
            if (item.getType() == type) {
                item.addQuantity(amount);
                return;
            }
        }
    }
    // 判斷玩家存活
    bool isAlive() const {
        return hp > 0;
    }

    // show info
    void showStatus() const {
        cout << "\n======= 玩家狀態 =======\n";
        cout << " 名稱: " << name << "\n";
        cout << " HP:   " << hp << " / " << maxHp << "\n";
        cout << " MP:   " << mp << " / " << maxMp << "\n";
        cout << " 攻擊: " << attackPower << "\n";
        cout << " 金幣: " << gold << "\n";
        cout << "==========================\n";
    }

    void showSkills() const {
        cout << "\n--- 技能列表 ---\n";
        for (size_t i = 0; i < skills.size(); ++i) {
            cout << "[" << i + 1 << "] ";
            skills[i].showInfo();
        }
    }

    void showItems() const {
        cout << "\n--- 背包中的物品 ---\n";
        for (size_t i = 0; i < items.size(); ++i) {
            cout << "[" << i + 1 << "] ";
            items[i].showInfo();
        }
    }

    // Getter
    string getName() const { return name; }
    int getGold() const { return gold; }
};
// battle
void startCombat(Player& player, Monster& monster) {
    cout << "\n遭遇了【" << monster.getName() << "】！\n";
    while (player.isAlive() && monster.isAlive()) {
        cout << "\n================ 你的回合 ================\n";
        player.showStatus();
        monster.showInfo();
        cout << "==========================================\n";
        cout << "【1】 揮舞武器 (普通攻擊)\n";
        cout << "【2】 使用技能 (施展技能)\n";
        cout << "【3】 翻找背包 (使用物品)\n";
        cout << "請選擇你的行動 (輸入數字): ";

        int choice;
        cin >> choice;
        cout << "\n";

        // act
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
            }
            else {
                cout << "取消施法，重新選擇行動。\n";
                continue;
            }
        }
        else if (choice == 3) {
            player.showItems();
            cout << "請選擇要使用的物品 (輸入 0 取消): ";
            int itemChoice;
            cin >> itemChoice;

            if (itemChoice > 0) {
                player.useItem(itemChoice - 1);
            }
            else {
                cout << "關閉背包，重新選擇行動。\n";
                continue;
            }
        }
        else {
            cout << "無效的選擇，浪費了一回合！\n";
        }

        // act monster
        if (monster.isAlive()) {
            cout << "\n================ 敵方回合 ================\n";
            monster.attack();
            player.takeDamage(monster.getAttackPower());
        }
    }

    // --- finish ---
    cout << "\n================ 戰鬥結束 ================\n";
    if (player.isAlive()) {
        cout << "🏆 勝利！\n";
        player.gainGold(monster.getRewardGold());
    }
    else {
        cout << "【YOU DIED】\n";
    }
}
void visitMerchant(Player& player) {
    cout << "\n你發現了營火，旁邊坐著一位穿著破布的神秘商人...\n";
    player.restoreStatus();
    bool merchantAlive = true;
    while (merchantAlive && player.isAlive()) {
        cout << "\n=============== 營火與商人 ===============\n";
        cout << " 💰 你目前持有: " << player.getGold() << " 枚金幣\n";
        cout << "【1】 購買 [枯血藥劑] (花費 15 金幣) - 恢復 30 HP\n";
        cout << "【2】 購買 [餘燼結晶] (花費 20 金幣) - 恢復 20 MP\n";
        cout << "【3】 購買 [狂人骨灰] (花費 25 金幣) - 永久提升 5 點攻擊力\n";
        cout << "【4】 攻擊商人，後果自負\n";
        cout << "【0】 離開營火，繼續旅途\n";
        cout << "==========================================\n";
        cout << "請選擇你要進行的交易 (輸入數字): ";

        int choice;
        cin >> choice;
        cout << "\n";

        if (choice == 1) {
            if (player.spendGold(15)) {
                player.buyItem(ItemType::HEAL_HP, 1);
                cout << "🎒 交易完成！獲得了 [枯血藥劑] x 1。\n";
            }
            else {
                cout << "❌  你太窮了。\n";
            }
        }
        else if (choice == 2) {
            if (player.spendGold(20)) {
                player.buyItem(ItemType::HEAL_MP, 1);
                cout << "🎒 交易完成！獲得了 [餘燼結晶] x 1。\n";
            }
            else {
                cout << "❌  你太窮了。\n";
            }
        }
        else if (choice == 3) {
            if (player.spendGold(25)) {
                player.buyItem(ItemType::BUFF_ATK, 1);
                cout << "🎒 交易完成！獲得了 [狂人骨灰] x 1。\n";
            }
            else {
                cout << "❌ 你太窮了。\n";
            }
        }
        else if (choice == 4) {
            cout << "你會後悔的。\n";
            Monster serect("神秘商人", 300, 15, 1000);
            startCombat(player, serect);
            if (player.isAlive()) {
                cout << "\n🎒 你殺死了商人！\n";
                player.buyItem(ItemType::HEAL_HP, 1);
                player.buyItem(ItemType::HEAL_MP, 1);
                player.buyItem(ItemType::BUFF_ATK, 1);
                cout << "✨ 獲得了 [枯血藥劑] x 1、[餘燼結晶] x 1、[狂人骨灰] x 1。\n";
                merchantAlive = false;
            }
            else {
                // Died
                merchantAlive = false;
            }
        }
        else if (choice == 0) {
            cout << "🚶 你離開了營火。\n";
            break; // 離開商人迴圈
        }
        else {
            cout << "❌ 商人疑惑地看著你... (無效的選擇)\n";
        }
    }
}
int main() {
    //player
    Player player("見習守墓人", 100, 50, 15);
    //skill
    Skill shadowStrike("黯影打擊", 25, 10);
    Skill requiem("鎮魂輓歌", 50, 25);

    player.addSkill(shadowStrike);
    player.addSkill(requiem);
    //item
    Item hpPotion("枯血藥劑", ItemType::HEAL_HP, 30, 3);
    Item mpPotion("餘燼結晶", ItemType::HEAL_MP, 20, 2);
    Item atkBuff("狂人骨灰", ItemType::BUFF_ATK, 5, 1);
    player.addItem(hpPotion);
    player.addItem(mpPotion);
    player.addItem(atkBuff);
    //monster
    Monster zombie("腐朽活屍", 30, 5, 15);
    Monster gargoyle("黑棘石像鬼", 60, 12, 50);
    Monster boss("深淵領主", 200, 25, 500);
    //start
    cout << "🔥 遊戲開始 🔥\n";
    player.showStatus();
    //first battle
    startCombat(player, zombie);
    //second battle
    if (player.isAlive()) {
        cout << "\n敵人出現\n";
        startCombat(player, gargoyle);
    }
    visitMerchant(player);
    //final
    if (player.isAlive()) {
        cout << "\nBoss出現\n";
        startCombat(player, boss);
    }
    if (player.isAlive()) {
        cout << "\n🎉 勝利，為村莊帶回火光！\n";
    }
    return 0;
}