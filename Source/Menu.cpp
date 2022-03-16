
#pragma once
#include "stdafx.h"

void main() 
{
	notifyMap("~b~Lean ~b~Menu ~s~v1.1 ~g~Loaded!");
	while (true) 
	{
		Menu::Checks::Controlls();
		godmode(GODMODE);
		invisible(INVISIBLE);
		superjump(SUPERJUMP);
		neverwanted(NEVERWANTED);
		moneydrop(MONEYDROP);
		remgodmode(REMGODMODE);
		freezeammo(FREEZEAMMO);
		remfreezeammo(REMFREEZEAMMO);
		rapidfire(RAPIDFIRE);
		tpgun(TPGUN);
		delgun(DELGUN);
		moneygun(MONEYGUN);
		freeze(FREEZE);
		fastrun(FASTRUN);
		timechange(TIMECHANGE);
		boost(BOOST);

		switch (Menu::Settings::currentMenu) {

		case mainmenu:
		{
			Menu::Title("Lean Menu");
			Menu::MenuOption("Self", player);
			Menu::MenuOption("Weapon", weapon);
			Menu::MenuOption("World", world);
			Menu::MenuOption("Recovery", recovery);
			Menu::MenuOption("Players", playerlist);
			Menu::MenuOption("Settings", settings);
		}
		break;

		case player:
		{
			Menu::Title("Self");
			Menu::Toggle("Godmode", GODMODE);
			Menu::Toggle("Invisible", INVISIBLE);
			Menu::Toggle("Super Jump", SUPERJUMP);
			Menu::Toggle("Never Wanted", NEVERWANTED);
			Menu::Toggle("Boost", BOOST);
			if (Menu::Option("Heal Player"))
			{
				ENTITY::SET_ENTITY_HEALTH(PLAYER::PLAYER_PED_ID(), 400);
				PED::ADD_ARMOUR_TO_PED(PLAYER::PLAYER_PED_ID(), 200);
			}
			if (Menu::Option("Teleport to Waypoint"))
			{
				Vector3 coords = get_blip_marker();

				if (coords.x == NULL && coords.y == NULL)
				{
					notifyMap("No Waypoint has been set!");
					return;
				}
				Entity e = PLAYER::PLAYER_PED_ID();
				if (PED::IS_PED_IN_ANY_VEHICLE(e, 0))
				{
					e = PED::GET_VEHICLE_PED_IS_USING(e);
				}

				bool groundFound = false;
				static float groundCheckHeight[] =
				{ 100.0, 150.0, 50.0, 0.0, 200.0, 250.0, 300.0, 350.0, 400.0, 450.0, 500.0, 550.0, 600.0, 650.0, 700.0, 750.0, 800.0 };
				for (int i = 0; i < sizeof(groundCheckHeight) / sizeof(float); i++)
				{
					ENTITY::SET_ENTITY_COORDS_NO_OFFSET(e, coords.x, coords.y, groundCheckHeight[i], 0, 0, 1);
					WAIT(100);
					if (GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(coords.x, coords.y, groundCheckHeight[i], &coords.z, 0))
					{
						groundFound = true;
						coords.z += 3.0;
						break;
					}
				}
				if (!groundFound)
				{
					coords.z = 1000.0;
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xFBAB5776, 1, 0);
				}
				tpToCoords(e, coords);
			}
		}
		break;

		case weapon:
		{
			Menu::Title("Weapon");
			if (Menu::Option("Give All Weapons"))
			{
				uint weapons[] = { 0x57A4368C, 0x917F6C8C, 0xAF3696A1, 0x476BF155, 0xB62D1F670, 0xDFE37640, 0xC1B3C3D1, 0x99B507EA, 0x678B81B1, 0x4E875F73, 0x958A4A8F, 0x440E4788,
					0x84BD7BFD, 0x1B06D571, 0x5EF9FEC4, 0x22D8FE39, 0x99AEEB3B, 0x13532244, 0x2BE6766B, 0xEFE7E2DF, 0xBFEFFF6D, 0x83BF0278,
					0xAF113F99, 0x9D07F764, 0x7FD62962, 0x1D073A89, 0x7846A318, 0xE284C527, 0x9D61E50F, 0x3656C8C1, 0x05FC3C11, 0x0C472FE2,
					0x33058E22, 0xA284510B, 0x4DD2DC56, 0xB1CA77B1, 0x687652CE, 0x42BF8A85, 0x93E220BD, 0x2C3731D9, 0xFDBC8A50, 0x24B17070,
					0x060EC506, 0x34A67B97, 0xFDBADCED, 0x23C9F95C, 0x497FACC3, 0xF9E6AA4B, 0x61012683, 0xC0A3098D, 0xD205520E, 0xBFD21232,
					0x7F229F94, 0x92A27487, 0x083839C4, 0x7F7497E5, 0xA89CB99E, 0x3AABBBAA, 0xC734385A, 0x787F0BB, 0x47757124, 0xD04C944D,
					1305664598,2803906140,4208062921,4222310262,3686625920,3415619887,3249783761,3125143736,2526821735,2285322324,2228681469,
					1432025498,961495388,177293209, GAMEPLAY::GET_HASH_KEY("WEAPON_HATCHET"), GAMEPLAY::GET_HASH_KEY("WEAPON_RAILGUN") };
				
				for (int i = 0; i < (sizeof(weapons)); i++)
				{
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), weapons[i], 9999, 1);
				}
			}
			if (Menu::Option("Remove all Weapons"))
			{
				WEAPON::REMOVE_ALL_PED_WEAPONS(PLAYER::PLAYER_PED_ID(), true);
			}
			Menu::Toggle("Infinite Ammo", FREEZEAMMO);
			Menu::Toggle("Rapidfire", RAPIDFIRE);
			Menu::Toggle("Teleport Gun", TPGUN);
			Menu::Toggle("Delete Gun", DELGUN);
			Menu::Toggle("Money Gun", MONEYGUN);
		}
		break;

		case playerlist:
		{
			Menu::Title("Online Players");
			for (int i = 0; i < 32; i++)
			{
				if (ENTITY::DOES_ENTITY_EXIST(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i)))
				{
					Menu::MenuOption(PLAYER::GET_PLAYER_NAME(i), playermenu) ? selectedPlayer = i : NULL;
				}
			}
		}
		break;

		case playermenu:
		{
			Menu::Title(PLAYER::GET_PLAYER_NAME(selectedPlayer));
			Menu::Toggle("Godmode", REMGODMODE);
			if (Menu::Option("Teleport"))
			{
				tpToClient(PLAYER::GET_PLAYER_PED(selectedPlayer));
			}
			if (Menu::Option("Teleport in Vehicle"))
			{
				if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::GET_PLAYER_PED(selectedPlayer), true))
				{
					PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), PED::GET_VEHICLE_PED_IS_USING(PLAYER::GET_PLAYER_PED(selectedPlayer)), VEHICLE::IS_VEHICLE_SEAT_FREE(PED::GET_VEHICLE_PED_IS_USING(PLAYER::GET_PLAYER_PED(selectedPlayer)), -1));
				}
			}
			Menu::Toggle("Drop Money (PATCHED)", MONEYDROP);
			if (Menu::Option("Drop Money"))
			{
				STREAMING::REQUEST_MODEL(0x113FD533);
				Vector3 player = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), true);
				if (STREAMING::HAS_MODEL_LOADED(0x113FD533))
				{
					OBJECT::CREATE_AMBIENT_PICKUP(PickupTypeMoneyCase, player.x, player.y, player.z + 3, 0, 2500, 0x113FD533, true, false);
					STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(0x113FD533);
				}
			}
			if (Menu::Option("Drop Paracute"))
			{
				Vector3 player = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), true);
				OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_PARACHUTE"), player.x, player.y, player.z, 0, 2500, 1, 0, 1);
			}
			if (Menu::Option("Drop Armour"))
			{
				Vector3 player = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), true);
				OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_ARMOUR_STANDARD"), player.x, player.y, player.z, 0, 2500, 1, 0, 1);
			}
			if (Menu::Option("Drop Medipack"))
			{
				Vector3 player = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), true);
				OBJECT::CREATE_AMBIENT_PICKUP(GAMEPLAY::GET_HASH_KEY("PICKUP_HEALTH_STANDARD"), player.x, player.y, player.z, 0, 2500, 1, 0, 1);
			}
			if (Menu::Option("Give All Weapons"))
			{
				uint weapons[] = { 0xAF3696A1, 0x476BF155, 0xB62D1F670, 0xDFE37640, 0xC1B3C3D1, 0x99B507EA, 0x678B81B1, 0x4E875F73, 0x958A4A8F, 0x440E4788,
					0x84BD7BFD, 0x1B06D571, 0x5EF9FEC4, 0x22D8FE39, 0x99AEEB3B, 0x13532244, 0x2BE6766B, 0xEFE7E2DF, 0xBFEFFF6D, 0x83BF0278,
					0xAF113F99, 0x9D07F764, 0x7FD62962, 0x1D073A89, 0x7846A318, 0xE284C527, 0x9D61E50F, 0x3656C8C1, 0x05FC3C11, 0x0C472FE2,
					0x33058E22, 0xA284510B, 0x4DD2DC56, 0xB1CA77B1, 0x687652CE, 0x42BF8A85, 0x93E220BD, 0x2C3731D9, 0xFDBC8A50, 0x24B17070,
					0x060EC506, 0x34A67B97, 0xFDBADCED, 0x23C9F95C, 0x497FACC3, 0xF9E6AA4B, 0x61012683, 0xC0A3098D, 0xD205520E, 0xBFD21232,
					0x7F229F94, 0x92A27487, 0x083839C4, 0x7F7497E5, 0xA89CB99E, 0x3AABBBAA, 0xC734385A, 0x787F0BB, 0x47757124, 0xD04C944D,
					1305664598,2803906140,4208062921,4222310262,3686625920,3415619887,3249783761,3125143736,2526821735,2285322324,2228681469,
					1432025498,961495388,177293209, GAMEPLAY::GET_HASH_KEY("WEAPON_HATCHET"), GAMEPLAY::GET_HASH_KEY("WEAPON_RAILGUN") };

				for (int i = 0; i < (sizeof(weapons)); i++)
				{
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED(selectedPlayer), weapons[i], 9999, 1);
				}
				notifyMap("~g~Successfully gave ~s~" + (string) PLAYER::GET_PLAYER_NAME(selectedPlayer) + " ~g~all Weapons!");
			}
			if (Menu::Option("Remove all Weapons"))
			{
				WEAPON::REMOVE_ALL_PED_WEAPONS(PLAYER::GET_PLAYER_PED(selectedPlayer), true);
				notifyMap("~g~Successfully removed all Weapons from ~s~" + (string)PLAYER::GET_PLAYER_NAME(selectedPlayer));
			}
			Menu::Toggle("Infinite Ammo", REMFREEZEAMMO);
			if (Menu::Option("Heal Player"))
			{
				ENTITY::SET_ENTITY_HEALTH(PLAYER::GET_PLAYER_PED(selectedPlayer), 400);
				PED::ADD_ARMOUR_TO_PED(PLAYER::GET_PLAYER_PED(selectedPlayer), 200);
			}
			Menu::Toggle("Freeze", FREEZE);
			if (Menu::Option("Kill Player"))
			{
				notifyMap("~bold~~r~This feature is currently unavalible.");
			}
		}
		break;

		case settings:
		{
			Menu::Title("Settings"); 
			Menu::MenuOption("Credits", credits);
			if (Menu::Option("Exit Game")) exit(0);
		}
		break;

		case credits:
		{
			Menu::Title("Credits");
			if (Menu::Option("Nano 42 Base")) system("start https://www.unknowncheats.me/forum/grand-theft-auto-v/270863-updated-nano42-base.html");
		}
		break;

		case recovery:
		{
			Menu::Title("Recovery");
			if (Menu::Option("1 Million Cash (PATCHED)"))
			{
				int var0 = 0ul;
				UNK3::_NETWORK_SHOP_BEGIN_SERVICE(&var0, 1474183246, 312105838, 1445302971, 1000000, 4);
				UNK3::_NETWORK_SHOP_CHECKOUT_START(var0);
			}
			int lvl;
			if (Menu::Int("Choose Level", lvl, 1, 8000))
			{
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept))
				{
					lvl = NumberKeyboard();
				}
			}
			if (Menu::Option("Set Level"))
			{
				setRank(lvl);
			}
		}
		break;

		case world:
		{
			Menu::Title("World Options");
			Menu::MenuOption("Time", timemenu);
			Menu::MenuOption("Weather", weather);
			Menu::MenuOption("Vehicle Spawner", vehiclespawn);
		}
		break;

		case timemenu: 
		{
			Menu::Title("Time");
			Menu::Toggle("Prevent Time from changing", TIMECHANGE);
			int timeHrs;
			if (Menu::Int("Set Time", timeHrs, 1, 24))
			{
				TIME::SET_CLOCK_TIME(timeHrs, 0, 0);
			}
		}
		break;

		case weather:
		{
			Menu::Title("Weather");
	
		}
		break;

		case vehiclespawn:
		{
			Menu::Title("Vehicle Spawner");
			Menu::MenuOption("Super Cars", super);
			Menu::MenuOption("Sport Cars", sport);
			Menu::MenuOption("Boats", boats);
			Menu::MenuOption("Bikes", bike);
			Menu::MenuOption("Offroad Cars", offroad);
			Menu::MenuOption("Planes", plane);
			Menu::MenuOption("Helicopters", helicopters);
			Menu::MenuOption("SUVs", suvs);
			Menu::MenuOption("Emergency", emergency);
			Menu::MenuOption("Utility", utility);
		}
		break;

		case super:
		{
			Menu::Title("Super Cars");
			if (Menu::Option("T20"))
			{
				createveh("T20");
			}
			if (Menu::Option("Zentorno"))
			{
				createveh("zentorno");
			}
			if (Menu::Option("Turismo 2"))
			{
				createveh("turismo2");
			}
			if (Menu::Option("Voltic"))
			{
				createveh("voltic2");
			}
		}
		break;

		case sport:
		{
			Menu::Title("Sport Cars");
			if (Menu::Option("Banshee"))
			{
				createveh("banshee");
			}
			if (Menu::Option("Comet"))
			{
				createveh("comet3");
			}
			if (Menu::Option("Omnis"))
			{
				createveh("omnis");
			}
			if (Menu::Option("Tampa"))
			{
				createveh("tampa2");
			}
		}
		break;

		case bike:
		{
			Menu::Title("Bikes");
			if (Menu::Option("Sanchez"))
			{
				createveh("sanchez");
			}
			if (Menu::Option("Oppressor"))
			{
				createveh("oppressor");
			}
			if (Menu::Option("Oppressor MK2"))
			{
				createveh("oppressor2");
			}
		}
		break;

		case offroad:
		{
			Menu::Title("Offroad Cars");
			if (Menu::Option("Blazer"))
			{
				createveh("blazer3");
			}
			if (Menu::Option("Dune 2"))
			{
				createveh("dune2");
			}
			if (Menu::Option("Nightshark"))
			{
				createveh("nightshark");
			}
			if (Menu::Option("Trophy Truck"))
			{
				createveh("trophytruck");
			}
			if (Menu::Option("Trophy Truck 2"))
			{
				createveh("trophytruck2");
			}
		}
		break;

		case plane:
		{
			Menu::Title("Planes");
			if (Menu::Option("Besra"))
			{
				createveh("besra");
			}
			if (Menu::Option("Hydra"))
			{
				createveh("hydra");
			}
			if (Menu::Option("Lazer"))
			{
				createveh("lazer");
			}
			if (Menu::Option("Luxor"))
			{
				createveh("luxor");
			}
			if (Menu::Option("Golden Luxor"))
			{
				createveh("luxor2");
			}
			if (Menu::Option("Airplane"))
			{
				createveh("jet");
			}
			if (Menu::Option("Titan"))
			{
				createveh("titan");
			}
		}
		break;

		case helicopters:
		{
			Menu::Title("Helicopters");
			if (Menu::Option("Weaponed Buzzard"))
			{
				createveh("buzzard");
			}
			if (Menu::Option("Buzzard"))
			{
				createveh("buzzard2");
			}
			if (Menu::Option("Skylift"))
			{
				createveh("skylift");
			}
			if (Menu::Option("Volatus"))
			{
				createveh("volatus");
			}
		}
		break;

		case suvs:
		{
			Menu::Title("SUVs");
			if (Menu::Option("Dubsta"))
			{
				createveh("dubsta");
			}
			if (Menu::Option("Armored Baller"))
			{
				createveh("baller6");
			}
		}
		break;

		case utility:
		{
			Menu::Title("Utility");
			if (Menu::Option("Airtug"))
			{
				createveh("airtug");
			}
			if (Menu::Option("Caddy"))
			{
				createveh("caddy");
			}
			if (Menu::Option("Caddy (No Roof)"))
			{
				createveh("caddy2");
			}
			if (Menu::Option("Special Caddy"))
			{
				createveh("caddy3");
			}
			if (Menu::Option("Forklift"))
			{
				createveh("forklift");
			}
			if (Menu::Option("Old Tractor"))
			{
				createveh("tractor");
			}
			if (Menu::Option("Tractor"))
			{
				createveh("tractor2");
			}
			if (Menu::Option("Snow Tractor"))
			{
				createveh("tractor3");
			}
		}
		break;

		case boats:
		{
			Menu::Title("Boats");
			if (Menu::Option("Jetski"))
			{
				createveh("seashark");
			}
			if (Menu::Option("Modified Jetski"))
			{
				createveh("seashark3");
			}
			if (Menu::Option("Tug"))
			{
				createveh("tug");
			}
			if (Menu::Option("Submarine"))
			{
				createveh("submersible");
			}
			if (Menu::Option("Special Submarine"))
			{
				createveh("submersible2");
			}
		}
		break;

		case emergency:
		{
			Menu::Title("Emergency");
			if (Menu::Option("Ambulance"))
			{
				createveh("ambulance");
			}
			if (Menu::Option("Fire Truck"))
			{
				createveh("firetruck");
			}
			if (Menu::Option("FBI Car"))
			{
				createveh("fbi");
			}
			if (Menu::Option("FBI Van"))
			{
				createveh("fbi2");
			}
			if (Menu::Option("Prison Bus"))
			{
				createveh("pbus");
			}
			if (Menu::Option("Standard Police Car"))
			{
				createveh("police");
			}
			if (Menu::Option("FBI inspired Police Car"))
			{
				createveh("police2");
			}
			if (Menu::Option("Special Police Car"))
			{
				createveh("police3");
			}
			if (Menu::Option("Criminal Police Car"))
			{
				createveh("police4");
			}
			if (Menu::Option("Old Police Van"))
			{
				createveh("policeold1");
			}
			if (Menu::Option("Old Police Car"))
			{
				createveh("policeold2");
			}
			if (Menu::Option("Police Van"))
			{
				createveh("policet");
			}
			if (Menu::Option("Police Bike"))
			{
				createveh("policeb");
			}
			if (Menu::Option("Police Helicopter"))
			{
				createveh("polmav");
			}
			if (Menu::Option("LSPD Emergency Van"))
			{
				createveh("riot");
			}
			if (Menu::Option("Sheriff Car"))
			{
				createveh("sheriff");
			}
			if (Menu::Option("Sheriff Van"))
			{
				createveh("sheriff2");
			}
		}
		break;

		}
		Menu::End();
		WAIT(0);
	}
}

void ScriptMain() {
	srand(GetTickCount());

	main();
}
