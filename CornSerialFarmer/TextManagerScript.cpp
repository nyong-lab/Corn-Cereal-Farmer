#include "TextManagerScript.h"

TextManagerScript::TextManagerScript()
	: MonoBehaviour(typeid(this).name())
{

}

TextManagerScript::~TextManagerScript()
{

}

void TextManagerScript::Start()
{
	vector<wstring> NPC1 = { L"농장주 양반이\n언제 이사를 했담?" , L"강낭이농사는\n잘 되가는감~", L"젊은 양반이 왜이렇게\n안색이 어두워!", L"젊은놈이\n싹박가지가 없구먼…", L"가정 교육을\n어떻게 받은겐가!", L"농장주 양반은\n싹싹헜는디말여…"};
	vector<wstring> NPC2 = { L"안녕하세요!\n날씨가 좋죠?" , L"제가 도와드릴게\n있을까요?", L"제 동생 못보셨나요?\n보라색 머리에요", L"왜 저러는거야?", L"무서운\n사람이다…", L"저 사람…\n수상한데…" };
	vector<wstring> NPC3 = { L"우리 언니\n못봤어요?\n노란색 머리인데" , L"저 옥수수\n내가 가져가도\n돼요?", L"저기\n들어가봐도 돼요?", L"으아앙~!\n언니이~!!", L"저 사람\n무서워~!", L"흥!\n이상한 사람이야!"};
	vector<wstring> NPC4 = { L"티라노랑 렙터랑\n싸우면 누가이길까요?" , L"이 근처에 공룡이\n있지 않을까요?", L"이거 티라노게요,\n알로사우르스게요?", L"안녕히 계세요~", L"공룡 싫어하시나…", L"어디 공룡\n화석같은거 없나…"};
	vector<wstring> NPC5 = { L"잠시 시간\n괜찮으세요?" , L"선생님! 기운이 참\n맑아 보이세요.", L"조상님께서 이 돌맹\n이를 구매하라시네요", L"한말씀만\n들어보세요!", L"종말이\n머지않았습니다!", L"떼잉…~~\n돌 좀 사가지…" };
	vector<wstring> NPC6 = { L"농장 주인분은\n어디간거에요!" , L"농장 주인분을\n숨겨둔거죠!", L"당신,\n나쁜사람이죠!", L"두고 봐! 농장\n주인을 찾아낼거야!", L"저 사람, 분명\n뭔가 숨기고 있어!", L"저 사람, 분명\n나쁜 사람이야!" };
	vector<wstring> Player = { L"일 없슈." , L"신경 끄쇼.", L"꺼져!" };
	vector<wstring> Police = { L"순찰 중\n이상 무!" , L"수상한 사람은 없나?", L"요새 실종자가\n부쩍 늘었어…"};

	ScriptMap["NPC1"] = NPC1;
	ScriptMap["NPC2"] = NPC2;
	ScriptMap["NPC3"] = NPC3;
	ScriptMap["NPC4"] = NPC4;
	ScriptMap["NPC5"] = NPC5;
	ScriptMap["NPC6"] = NPC6;
	ScriptMap["Player"] = Player;
	ScriptMap["Police"] = Police;

	vector<wstring> farm = { L"옥수수를 키울 수 있는\n빈 밭이다.", L"옥수수 씨앗을\n심은 밭이다.", L"밭에 새싹이 자랐다. ", L"옥수수가 무서운 속도로\n 성장중인 밭이다.", L"옥수수가 다 자랐다. \n이제 수확할 수 있겠군."};
	vector<wstring> house = {L"평범한 가정집이다.\n누가 들어오지만 않는다면\n시체를 숨기기 적당할 것이다."};
	vector<wstring> wareHouseA = {L"옥수수와 씨앗을 보관하는\n작은 창고다. 집 옆이라 누가 시체를\n보기 전에 쫒아내기 좋을 것이다."};
	vector<wstring> wareHouseB = {L"물뿌리개 등 기자재를 보관하는\n큰 창고다. 시체 하나쯤 숨겨도\n모를 정도로 넓다."};
	vector<wstring> wareHouseC = {L"수확에 쓰일 자루 등을 보관하는\n작은 창고다. 길 옆이라 불안하지만,\n시체를 숨길 수 있을만한 공간이다."};
	vector<wstring> wareHouseD = {L"도끼나 비료포대처럼 자주 쓰는\n것들을 보관하는 창고다.\n인적이 드물어 시체를 숨기기 좋다."};
	vector<wstring> truck = {L"수확물을 운반하는 트럭이다.\n운전은 할 수 없지만 시체정도는\n숨길 수 있을 것이다."};
	vector<wstring> pond = {L"밭 옆의 깊은 물웅덩이이다.\n바위가 미끄러우니\n빠지지 않게 조심하자.", L"물이 오염돼서 사용할 수 없다."};
	vector<wstring> catHouse = {L"고양이가 사는 집이다.\n…귀여운 녀석 같으니라고."};
	vector<wstring> catbowl = {L"고양이의 밥그릇이다.\n …든든하게 먹으라고."};
	vector<wstring> tree = {L"여기 나무는 뗄감으로 쓰기\n좋아보인다. "};
	vector<wstring> NPC1ex = {L"여기저기 들쑤시고 다니는\n꼰대 할배다."};
	vector<wstring> NPC2ex = {L"쓸데없이 오지랖이 넓은\n꼬맹이다."};
	vector<wstring> NPC3ex = {L"짜증나는 꼬맹이다."};
	vector<wstring> NPC4ex = {L"맨날 공룡 어쩌고 거리는\n꼬맹이다."};
	vector<wstring> NPC5ex = {L"돌팔이다. 장난이 아니고,\n진짜 돌을 팔더라니깐."};
	vector<wstring> NPC6ex = {L"시끄러운 꼬맹이다."};
	vector<wstring> wildBoar = {L"저놈의 멧돼지가\n또 밭을 망치러 왔군…!"};
	vector<wstring> cat = { L"귀여운 고양이다.\n 쓰다듬어 주고 싶군..." };
	
	explainMap["FARM"] = farm;
	explainMap["House"] = house;
	explainMap["WareHouseA"] = wareHouseA;
	explainMap["WarehouseB"] = wareHouseB;
	explainMap["WarehouseC"] = wareHouseC;
	explainMap["WarehouseD"] = wareHouseD;
	explainMap["Truck"] = truck;
	explainMap["Pond"] = pond;
	explainMap["CatHouse"] = catHouse;
	explainMap["CatBowl"] = catbowl;
	explainMap["Tree"] = tree;
	explainMap["npc1"] = NPC1ex;
	explainMap["npc2"] = NPC2ex;
	explainMap["npc3"] = NPC3ex;
	explainMap["npc4"] = NPC4ex;
	explainMap["npc5"] = NPC5ex;
	explainMap["npc6"] = NPC6ex;
	explainMap["wildBoar"] = wildBoar;
	explainMap["blackCatChild"] = cat;

	
}

void TextManagerScript::Update(float deltaTime)
{

}

void TextManagerScript::Finalize()
{

}
