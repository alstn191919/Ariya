/////////////////////////
//      FRYRENDER      //
//  (c) Feversoft, SL  //
//---------------------//
//  www.fryrender.com  //
/////////////////////////

FRMVersion 256

materialDef
{
	type layered

	paramsDef
	{
		alias "FRYRENDER Material 008"
		Opacity
		{
			active 0
			factor 50.000000
			path "Holes_transparency.jpg"

			submapDef
			{
				type bitmap

				uvwDef
				{
					tile_u 3.00000
					tile_v 3.00000
					tile_w 3.00000
				}

				imageDef
				{
					path "C:\feversoft\fryrender\materials\My materials\Holes_transparency.jpg"
				}
			}

		}

	}

	displacementDef
	{
		Displace
		{
			active 0
			factor 50.000000
			path "Holes_displace.jpg"

			submapDef
			{
				type bitmap

				uvwDef
				{
					tile_u 3.00000
					tile_v 3.00000
					tile_w 3.00000
				}

				imageDef
				{
					path "C:\feversoft\fryrender\materials\My materials\Holes_displace.jpg"
				}
			}

		}

		height 0.50000
		water_level 0.20000
	}

	toonDef
	{
		mode 1
		Color0
		{
			mode rgbsl
			rgb 15790320
		}

		Map0
		{
			active 0
			factor 50.000000
			path ""

			submapDef
			{
				type bitmap

			}

		}

		Color1
		{
			mode rgbsl
			rgb 15790320
		}

		Map1
		{
			active 0
			factor 50.000000
			path ""

			submapDef
			{
				type bitmap

			}

		}

	}

	previewDef
	{
		room 1
		ss 1
		passes 100
	}

	layerDef
	{
		type basic

		blendingDef
		{
			Map
			{
				active 0
				factor 50.000000
				path ""

				submapDef
				{
					type bitmap

				}

			}

			alias "Metallic"
		}

		reflectanceDef
		{
			Color0
			{
				mode rgbsl
				rgb 723723
			}

			Map0
			{
				active 0
				factor 50.000000
				path ""

				submapDef
				{
					type bitmap

				}

			}

			Color1
			{
				mode rgbsl
				rgb 14474460
			}

			Map1
			{
				active 0
				factor 50.000000
				path ""

				submapDef
				{
					type bitmap

				}

			}

		}

		fresnelDef
		{
			nd
			{
				index 1000.000000
				custom 0
				cutoff 0.000000
				bending 0.000000
			}

		}

		roughnessDef
		{
			roughness 40.00000
			Roughmap
			{
				active 0
				factor 50.000000
				path "Noise"

				submapDef
				{
					type noise

					colorDef
					{
						Color1
						{
							mode rgbsl
							rgb 1052688
						}

						Color2
						{
							mode rgbsl
							rgb 15790320
						}

					}
				}

			}

			Anisomap
			{
				active 0
				factor 50.000000
				path ""

				submapDef
				{
					type bitmap

				}

			}

			Rotmap
			{
				active 0
				factor 50.000000
				path ""

				submapDef
				{
					type bitmap

				}

			}

			Bump
			{
				active 0
				factor 50.000000
				path "Holes_displace(Normal Map).jpg"

				submapDef
				{
					type bitmap

					uvwDef
					{
						tile_u 3.00000
						tile_v 3.00000
						tile_w 3.00000
					}

					imageDef
					{
						path "C:\feversoft\fryrender\materials\My materials\Holes_displace(Normal Map).jpg"
					}
				}

			}

		}

		transmittanceDef
		{
			Color
			{
				mode rgbsl
				rgb 15461355
			}

			Map
			{
				active 0
				factor 50.000000
				path ""

				submapDef
				{
					type bitmap

				}

			}

		}

		sssDef
		{
			Color
			{
				mode rgbsl
				rgb 16777215
			}

			Map
			{
				active 0
				factor 50.000000
				path ""

				submapDef
				{
					type bitmap

				}

			}

		}

		coatingDef
		{
			Thickmap
			{
				active 0
				factor 50.000000
				path ""

				submapDef
				{
					type bitmap

				}

			}

		}

		coa_reflectanceDef
		{
			Color0
			{
				mode rgbsl
				rgb 8421504
			}

			Map0
			{
				active 0
				factor 50.000000
				path ""

				submapDef
				{
					type bitmap

				}

			}

			Color1
			{
				mode rgbsl
				rgb 15461355
			}

			Map1
			{
				active 0
				factor 50.000000
				path ""

				submapDef
				{
					type bitmap

				}

			}

		}

		coa_fresnelDef
		{
			nd
			{
				index 1.700000
				custom 0
				cutoff 0.000000
				bending 0.000000
			}

		}
	}

	ditherDef
	{
		pal 0 53 "928564596D898D74260A45A29E9A967B4D695E1F0631A6AAAE8154B5B9BEC2C639C93FB2CD49D10E35D4D870DC12782C51E0E41B17"
		pal 1 53 "928564596D898D74260A45A19E9A967B4D695E1F0631A5AAAE8154B5B9BEC2C539C93EB1CD49D00E35D4D870DC12772C50E0E31B17"
		pal 2 53 "928564596D898D74260A45A29E9A967B4D695E1F0631A6AAAE8154B5B9BEC2C639C93FB2CD49D10E35D4D871DC12782C51E0E41B17"
		hex 0 "FF07000102030401050501FF090506050606000000060606FF27000708090A00FF0D0BFF040C0BFF070CFF090D0EFF0D000606FF060501050101010F03100304FF070704"
		hex 1 "FF081102030302FF090407040404FF30071213141504FF1207FF1304FF0511020211FF0C02FF0412031010031212FF0703"
		hex 2 "01FF07050104030400FF0C0BFF0C16FF151718FF0E170615090A05FF060D0E0D0E0D0D0D0E0E0EFF0F000600FF0406FF0605FF0A01FF06190F0F041A1A070105FF0801"
		hex 3 "0D0D0DFF060C05110205181B1B1C1B1BFF061CFF121DFF0F1E1FFF061E1F1FFF061E0B2009100CFF0C17161717FF07160B0B1616FF080BFF060CFF040D0E0D0EFF090006060601021A02000C0C0C0D0C0D0D0D0E0E"
		hex 4 "0DFF050C0B0C0C0C1912040C1B1C1C1BFF051CFF091D1E1E1DFF081E1F1E1E1E1F1F1EFF0A1F1E1F1F1EFF051F1E1F1F1E162009100BFF10171617FF0A16FF080BFF060CFF050D0E0EFF09000507030301FF050CFF060D"
		hex 5 "FF040CFF060B00070201181C1C1C1D1C1C1CFF0A1DFF051E1F1E1E1F1E1E1F1F1EFF071F21FF061F21211F1F211F21FF061F162009100B1717FF0618FF09171617FF0816FF0A0BFF040CFF070D0E000EFF070001021A070D0B0BFF060C0D0D0D"
		hex 6 "FF040CFF070B0502110D1C1D1D1D1CFF081DFF0C1E1F1E1F1E1F1F1F1E1F1F21FF051F211F1F1FFF08211F211F1F1F172209100BFF0918171718FF051716FF0417FF0816FF080BFF040CFF070D0EFF070005071A0200FF050BFF040C0D0D0D"
		hex 7 "0B0C0B0CFF070B0C0F020F17FF071D1E1E1D1D1D1E1F1E1E1E1F1FFF041EFF041F1E1F1F21FF081F2121211FFF05211FFF0821172209100B23FF0C1817171718FF0817FF05160B0B16FF050BFF040CFF080DFF070019120301FF050BFF060C0D0D"
		hex 8 "FF0C0B000702061BFF071DFF0B1EFF041F2121FF051F211F21211F21211FFF052124212124FF062124212121180A09100BFF1218FF07171617FF0516FF060B0C0BFF050CFF070D0E000000050403070DFF070B0C0BFF040C"
		hex 9 "FF090B160B0B0B0502040BFF061DFF081E1F1F1E1F1F1FFF04211F21211F1FFF162124FF0421180A091A16FF041B181B1BFF0A1817FF0418FF0617FF0416FF060B0C0BFF060CFF050D0E0D0E00000F030206FF0A0BFF040C"
		hex 10 "FF090B16160B160B0F02011B1D1DFF051E1F1F1E1E1F1EFF061F21211F1E1E1D1E1FFF0521242121211E1D1D1EFF0521FF0624FF04211B0A091016FF081B181B1B1818181716160B0B0B16FF08171616160B160B0C0D0D0C0B0B0BFF040CFF060D0E0D000102030F0B1616FF070BFF040C0D"
		hex 11 "FF040B1616160BFF06160004040D1CFF061E1F1E1E1F1F1FFF07211F1C0C05050C1CFF05212421211E0B0501001C21FF04242124242421242421241B10091A16FF041B18FF071B170C0519FF050F01000C16FF04171616160B0C0107070F0D0B0B0BFF040C0D0C0CFF040D0E000703040DFF080B0C0C0D0D0D0005"
		hex 12 "000E0C0B0BFF06161717170B05020F171DFF051E1F1E1F1F2121211F1CFF041B180B0111110F0C1B1D1CFF051B17050402070C1B1E24242421FF08241C10091A161B18FF071B18181816000F0F0101010F0402110700160B0C0DFF04000104030304050D0C0CFF050D0EFF060019030301FF050C0D0D0CFF040D00010712"
		hex 13 "0207050B160BFF06161717170B0F11001C1E1E1F1F1EFF041F211F211E0B190707070F0F0411020207010C000F07070F0F0F0711020207051721242421FF08241C10091A16FF091B182318181616FF04170B01110202190D0F110212FF04031A101A03020F060600060606FF0505010501021A0400FF040D0EFF07000102100A"
		hex 14 "020F000BFF06161716FF04170D0407161E1F1F1F1E211F21211F1F211F1B0007110F000B0D0F11020F0B1B17010404010C160E07021101171C2121FF0A241C10091A16FF051B1823FF041B1818160C0D0C0C0E0507020207060004100A0A1A031A0A222210121107FF050F190F0F190F190F0F0410030F0600060000000606000606051902250A0A"
		hex 15 "1204001616161716FF0817160104011C211F2121211FFF052124211D160107010B1B0E04020F18211F1C0D0F07001B1B011111051DFF082426FF04241C1A271A17FF081B181B1B1B17000704070FFF04071906060F020A202210031A2220201002021111FF0504070704070707041025110105FF060105010101191110220A10"
		hex 16 "0312070C1616FF0B170B0F040C1EFF0921242121241F1C0B0F0F01050702070C1F24241F1805071900011102191C24242426FF06242624241D1A270317FF0C1B17050404010D0C0D0D00010F040202030A2022250A20282203FF050211FF06021104111A221A070FFF051901FF0519071A22221A11"
		hex 17 "031202010BFF071718171818181700040F1B1F21242121FF0424FF04212424211B0D0F07041104051D242626241D0B19070411020F1B242424262624242426FF04241D03270317FF0C1B160111110F1919071103020202031A12030AFF052010FF0F0203220A02FF04070F0707FF060F041A0A220A03"
		hex 18 "0F0F0F190C161717181817181817FF0418170104001EFF09242621FF0424261F180D0605000C1D2426292626241B0D060505001C242626262426262929262626241D032703181B1C1B1C1BFF061C1B170019070412031010101A1A100A0A120203100A0A0A1003FF0F0210201A04FF0E0711031A1010"
		hex 19 "FF040B16171717FF06181B1B181B180B0F071721FF0824262626242424262424211F2121212426292626292926242121212424FF0626FF04292626291F122703181B1C1C1C1BFF041C1B1B1B170B050F040202121A100A0A0A220A03020212020212FF10021A220A11FF0A07040707040707FF0404"
		hex 20 "161616FF07171818FF041B18181B1B0004011C21FF042426242624FF0726FF0429262926292926FF10292A2929262629291F02270318FF081C1B1B170D010F040402121A10FF050A220A1AFF1502120A2212FF1107042B0707"
		hex 21 "16FF0417181717FF06181B1B181B1B1B1701040B1F2426242426242426262426292926262629292926FF0429262629292A2C2A2929FF042AFF04292AFF04292A29210227121BFF051D1C1B180B000F040411020310FF0A0A10FF150210221A04FF10072B072B2B07"
		hex 22 "FF0517FF041823181818FF081B0B0F0F1B24262629FF0726FF0B292A2926FF072A29FF062A29FF082A24112D021C1D1D1D1C1B170D0107041102031A10FF0C0A10FF140203220A02FF1607"
		hex 23 "FF0617FF0618FF0A1B0007001F2626FF0C29FF052A292A2A2A292C2A2A2A2C2A2929FF0A2A2C2A2A2A2C26042D121B1D1C1B0B000F07040212031010FF0E0A25FF04021111FF0A0211020202102203FF1707"
		hex 24 "1718171818181718181B1818FF0A1B170107182426FF04292629292AFF04292A2A292A2A2A292A2A292C2A2A2A2C2C2A2A2A2C2C2A2A2C2AFF082C29072D1218170D0107040402031A10250A2525FF0E0A121102020211021102021102020211020211021A221004FF1707"
		hex 25 "0E000EFF090DFF050C0B0B0C0B0B0B05020F171B1B1C1C1B1B1C1C1DFF061C1D1D1D1CFF061D1CFF0F1DFF041E1D1B02270A2E04021202121A101010250AFF0425FF0D0A1AFF11031A22201AFF1802"
		hex 26 "111111FF1504030A1AFF0C0407040404FF05070407070704FF070704FF0A070402032F09132220200AFF091025251025250A0A25FF080AFF12222F0815FF1920"
		hex 27 "1B1C1D1D1C1D1CFF051D1E1E1D1DFF081E1B01070CFF0718FF1A1BFF071C1B1816000F11202720031AFF101025FF0A0A1A040707FF040407FF040407070704120A0A03FF06021212021212FF0402FF0A12"
		hex 28 "1F1FFF0521242121242424FF0526FF052926261B0F051BFF0B1D1E1DFF071E1F1FFF051E1F1F1FFF05211F1E1D1B1600190704022522FF1410250A0A2525FF050A1A07FF0E0F071A0A03021104041104111111041102040404FF0611FF0502"
		hex 29 "1FFF0621FF072426292624FF0729240C0F0C1C1D1D1E1D1D1D1E1D1DFF0B1EFF071FFF06211E1D180D0107041102031AFF171025250A25FF050A1004FF0E0F020A1002040404110404111111040411110404FF0611FF0502"
		hex 30 "FF0521FF05242624262424262626FF08291E0101181D1D1D1E1E1E1D1E1E1E1FFF041E1F1E1E1F1E1F1FFF07211F1F1D1B0B060F040402031AFF1C1025FF060A1011FF0D0F04100A1211040404110404041111110411110404041104FF0511020202"
		hex 31 "1E1F1F1F21FF072426262426FF07292A2A2929180F001CFF061EFF041F1E1EFF041F1E1F1F1F21242121211F1F1E1C170D1907040212031AFF1F102510250A250A2502FF0C0F07120A1A11FF09041104FF051104041111110411FF0402"
		hex 32 "0D0C0B161B1D211E170B0B0B1617181C2129292A292929FF042A240D0F171E1E1E1D1E1EFF061F1E1F1F1F1C170B171E241E170B0C00010711020202031AFF0A101AFF1B10250A2512FF0C0F04251002FF0A040212FF0603021102120303FF041A"
		hex 33 "0B0C0D1907010B1C160B1617160C0119001B24FF04292CFF042A1D01061C1F1E1E1F1F1F1E1F1F1F1C160B0B160C010F190C1B1B0E19070203100A101A1A1A1010101AFF04101A10101A1A1A1010101AFF161025250307FF0A0F07030A12FF09041112100A101A031022221A0202FF0403102222"
		hex 34 "17160C010404011B211F1B181816000707051E29FF042A2C2C2A2C2A17190B1EFF051F1E1F1E1F1C0C1919000B000F07010E000F021212031A1010101AFF05101A1A1A30FF071A10101A1010101AFF1310251A07FF0A0F020A1AFF090411030A220A0303032522251202FF0503100A0A"
		hex 35 "170B0B0D01070F0C1D1F171907010D0C0B1B2129FF052AFF042C240E011B1E1F1F211F1F1F2121211E1B0D060000071202040412101030101AFF04101A1AFF0410301A101A1A10FF041A301A1A1AFF17101A07FF090F071A1002FF09040210220A10031A1A03120212100A101A1A03030302"
		hex 36 "1B0B0C0C000F040F161F1E0B19010E0B0B0B181FFF052A2C2C2C312C1D010D1E1FFF04211F21212421211D0B0F02100A0A03031A10101A1A101010FF161A101A1A101A1AFF1210040F1919FF060F020A12FF0A0411030A0A100303030204021A0A0A101A1A1A121104"
		hex 37 "1F1D1C1B1B18181B1F2424211D1BFF041C1D212A2A2A292AFF042C312A1701171FFF08211E1B0B010402031AFF06101A1A10FF051A3010FF141A101A1A1A101AFF0F10020FFF06190F04101AFF0C041102021212120204040402FF051202020404"
		hex 38 "2121212424212424242626292624FF07292C2A2A2A2C2A2C3132322400001D21212421211F1C16060F04021203FF071A1010FF241A1010101AFF0A10120F0F19190F19190F03100204040407FF1C04"
		hex 39 "21FF09242626FF05292A2929FF062A2C31312C312C1D011621211F1D180D190402020303FF311A101AFF0A10030FFF05190F041003040407FF1D0407"
		hex 40 "1F2121212424242124FF0526FF05292A2A292A2A2C2A2A2A2C3131312A0B05181B0B05070402120303FF361AFF0910030FFF0519071A100407FF1A0407FF0504"
		hex 41 "FF05171817FF0618FF0B1BFF041C1BFF041D161919010712030303FF361A10FF041A101AFF05101A02FF0504030A03FF2202"
		hex 42 "17161617171716171817FF04181BFF0518FF051B1C1C1B1BFF041C1B0C0F050F03FF2C1A030303FF0F1A1010101AFF041012FF0404122503FF0A070FFF05070F0FFF04070F070F0F07070F070FFF0407"
		hex 43 "1B1B23FF061B1C1C1D1C1C1D1CFF041DFF071E1F1E1E1E1F1F1D00020303FF261A031A1AFF05031A1A031A1A1A03FF0D1AFF04101A1207070704031A0701190119FF090119FF04011919FF0A0119FF0401"
		hex 44 "FF081BFF051C1D1C1CFF041D1E1DFF041E1F1F1E1E1E1F1F1702FF241A03031A031AFF05031A031A1A03031A1A1A031A1A03FF0D1A10100304070702100419FF2301"
		hex 45 "16FF071B1C1C1B1BFF04181B1B1C1D1CFF041B1C1D1D1E1F1F1E1F1B02FF171A0303FF041A03031A03031AFF13031AFF0403FF0F1A030707041A030FFF080119FF060F010119FF050F190105FF0401050501051911"
		hex 46 "010B231B1B1B1C1B1C1B180B0D0D0D0001010C1B160119000B0D060C1C1E1F1E1E1D07FF191A03031A1AFF1F03FF0E1A030407121A07FF05010505010403030211031A020F0412120211031A02190101FF06050F0203"
		hex 47 "0B010D18FF041B1C1C1B1C1B160D0019071916170107010D00010117FF041E1D01FF1A1A03031A1AFF22031A1A031A03FF051A0304041A0401FF06050107101012041112120404101012041112020FFF0705010F020207"
		hex 48 "1E18050017FF041B1C1B1C1C170D0C00190F001B180D05000D0C0B171D1E1F1F1F00031A1A1A10FF121A03031AFF2B03FF061A0212120100000605050600060703031104040F01010403030404070F01FF05060005050F02110F0F"
		hex 49 "1E1F1B000016FF061B1C1B1818171717181C1D1D1C1B1B1B181B1D1D1E1E1E16031010FF131AFF3103FF041A03030F00000E0DFF0600FF050105000005FF0501FF0800050702070F0F0F"
		hex 50 "1E1F1F1C0C050B18FF051BFF081C1D1D1E1EFF041D1E1D1D1E1E180210101A1A10FF0E1A031AFF33031A030307000D0C0C0D0CFF060D000D0D0E0E0D0000000E0DFF090005040207FF0419"
		hex 51 "1C1D1E1D1C0B010D1718181823FF0C1BFF071C1D1D1B041010FF101AFF390301FF070D0E0D0DFF1500010402070FFF0419"
		hex 52 "FF060B00190616171718181B1818FF091B1C1B1BFF051C1B191A101010301A1010FF0A1AFF1A0312FF04031203030312FF060312FF0E030F05FF100119010101FF08190F0402070F1919190F1919"
		hex 53 "1616FF05170B050D1C1E1F21242121FF0424FF05262926262929262A2A290C1A101010FF0B1A031A03031AFF0F0312FF0403FF0412030303FF0B120312FF0F030FFF0C000600060506FF05050105FF05010704010E0E0D0D0E000000"
		hex 54 "16FF07171600001B1F212121FF0A24262929262426292A2A1803101010FF0D1AFF1103121212031203FF1412FF0F03070D0D0E0E0EFF090005060006000006000006050505010704050D0C0C0C0D0D000000"
		hex 55 "000C0B161716171717160000181F2121212424241F1B1B18170C161D241D17161B21291D021010FF0D1AFF1003FF2012031212FF080304000C0D00010F0F190F070100000F040705FF060006060519070F00FF040C0D0D0D010411"
		hex 56 "010F19060C1616171817160C05161E2121242421211F1C170B010F0C1F211D170C00161B04FF0510FF091A0303031AFF0C0312121203FF09120202FF0412021202FF1012FF0603110E0C0C0511020F0F07070100000102030FFF0700061907190EFF040C0D000000011210"
		hex 57 "05011901050C1617161617170C060C1C1F21FF041F1E1B18160D0B1E211C1B180B0B0B0F101010FF081A03FF041A031AFF0A031203FF0E12FF060212020202120202FF0C12031203030302000B0C0E011901010500060101190F070FFF0600060F07050D0C0B0B0C0C0D050101190704"
		hex 58 "0C0C0CFF050B16161617160B00001B1E1E1F1F1F21FF051F242424212124241F001A101010FF071A031A1AFF0D03FF0712020212120212FF1502121202FF09120302050B0B0BFF060C0D0EFF0A00050F0700FF050B0C0C0D0D0D0E000000"
		hex 59 "0D0D0C0DFF040CFF070B0606161B1BFF061C1D1CFF081D0C031010FF081A031A1AFF0A0312030303FF0412021202020212FF1B02FF0A12190C0B0CFF060D0E0EFF0800050107070500000EFF060006FF0505"
		hex 60 "0BFF05161717181717FF05180B05000B0BFF0416FF0517FF041817180C03301010FF081AFF0A031203FF0812FF25021202FF041219FF0517FF0616FF050B0C0C0C000707010501010505FF06011919190F0F"
		hex 61 "FF041617181817171818181B1C1C1C1D1800000BFF0817161617171818170B021A10FF071A031AFF0C03FF0612FF2A021212120F1718171818FF0B17160B000F19050605060505FF06011919190F0F19"
		hex 62 "0D00010105000C000105060100171B1C1C1C1800050C16FF0417160B0E000501000B0519021A101030FF061AFF0B03FF0612021212FF180211FF1002120202110000010D0D19010519010BFF0417160B000F010000060506050104020701190402111102040F"
		hex 63 "0B0B0D00010F010C00190101190D18FF051B0C050DFF06160C00050F010B0D19023010FF081AFF0903FF0812FF0E02FF0611FF0402FF0511FF130201000D0B050F010F190D16171717160B050F010000060505010F0F0412041907FF0402040F0F"
		hex 64 "FF050B0C0BFF05160B1718FF061B0B05000B0B0B1616FF050B16160B0103FF091AFF0903FF0512FF0E02110211111102FF04110404FF0A11FF0F0206171718160B0B0B1617171616160C010F050006060505FF04011919190119FF070F"
		hex 65 "FF07000E0DFF040CFF070B160B0D19010DFF060B16160B1617000330FF061AFF0A03FF0612FF0D02FF0711FF0D04FF071102111111FF0702010B0BFF080C0D0D060F0F0506FF0405FF0701190119FF060F07"
		hex 66 "0F0101FF0405FF09000EFF040D0C0C000106161818FF081B170210FF071AFF0803FF0412FF0902110202FF0811FF12041104FF0811FF06020FFF0A0006010F000D0C0C0D0D000EFF0500FF0506FF0405010F04"
		hex 67 "010F0F01050506060501190F19010605FF0401000D0C0C0D050516FF051B1816160C0002FF051AFF09031203FF0412FF070211020211041111110411FF1C0411110411FF05020401010F05FF0500060F0F00FF040C0D000F19000005010F070F05000006060501070404"
		hex 68 "0519070407040F191901010F070719010F0F0F0719000D0006010707060D0B0B1718160C000F02FF051AFF08031212031212FF0C02FF0411FF230411FF0402110F0F07010000190F0104040101000C0D00050104040101070F07040F010F0F07070402020207"
		hex 69 "190704021A0A1A021207FF060F0704070F010105010F0412031A12190705FF040C0D0FFF051AFF0803FF0412FF0A02111111FF12042B0707FF1304FF0411040F0119011907111A1A03040704190505010119070407FF060F04031A0A0A0A1A030302"
		hex 70 "15152F2F2F13130808FF07152F0808151528FF04152F15081315152020202222202210FF041AFF0703FF04120212FF0902111111FF0E04FF0607FF080407FF0D041111021A28FF04152F13332FFF05152815151508082FFF06152F0808341313FF0408"
		hex 71 "FF0520151320222222FF060A201522FF080A2208152222FF040A22101A1A1AFF0903121212FF0902111111FF0C0407070404FF1007040707FF0A041111110325FF050A0808FF0920282F15FF042028202015151308FF0620"
		hex 72 "FF050F040A0F0600000EFF040D0E0107000CFF070B00100700000EFF040D0E041A1AFF0803121212FF0802111111FF0B04FF1C07042BFF09040F0C0B0C0D0D000303FF09010F02070F19FF050F0707101A0F01190F1919"
		hex 73 "0101010F0F04101905000C0B0B0B160B000101001717171818170C0C0E030F000D0B0B1616160B071A1A1AFF0603FF0512FF05021111041111FF0904FF2007FF0904070B17160D000B021A040705FF050006190F070F05050101010F07071A1A0F1901050505"
		hex 74 "01010F100A100A120302050B0B16160B000F0F051617181817000402020A1003040D0B1616160B19FF0803121212FF090211040411FF06040704FF14072EFF0E07FF0704070B181700020004151A1A04FF06000F040207010501011903100A2020101A04010505"
		hex 75 "010119030A0210252E02040B0B1616160019190C1718181B180B000F10221A0F03010BFF041605FF0803121212FF0602FF0411FF0804FF13070F07070FFF1107FF0504070D17170B0207072207040305FF0400060F11110F050505010F2503102F2F12021A010505"
		hex 76 "0105010F1A100A100007020CFF05160B0B1717FF0418160103030A1100120F0B161616170D02FF0603121212FF07021111FF0704FF0D070F07070F07FF0C0F070F0F070FFF0B07040404001818170112040A190F1A01FF0500050101FF040501190320202228070F100F0505"
		hex 77 "01050101042022100004040C1616FF0517181718181B1B16061202100200121916161617160B04FF06031212FF07021111FF0704FF0D07FF160FFF0C070404070517170B00031A2204041A05FF07000606FF0405010320202228040F100F0605"
		hex 78 "01050F021A20101A0203190B160B1616161717171616181B180D0F0202031A0412001616160B0B0B0FFF0403121212FF070211FF0704FF09070F070707FF1A0F2EFF0C070117160F040310101A1A04FF04000600000005010105050101030A0A2020100310010605"
		hex 79 "010119111202040F07190C160C19070F19000B01070F0D181B0B191906070707050B160B050F0F010F030303FF0412FF060211FF0804FF0807FF0E0F190F1919FF100FFF0A070F16170B0C0D010701010000000607070500060F1102040101010F02031203110207050601"
		hex 80 "01FF04050F070C0B0B16160D041207010005040F0407161B1B181B0B190D0B0B16170B01010F04041203FF0412FF0702FF0704FF0807FF080F190F0F19190F0F190F0F0FFF0419FF100FFF07070F0B1818181700070000000E000007120F000102121103040105010119070205060000060F"
		hex 81 "FF0505070F0B16160B160B05020F0C0B0F070B05040CFF041B16190C0B161617160B0C0604041203121212FF05021111FF0504FF0A07FF080F19190FFF051901FF0D19FF0D0FFF05070DFF0418000F000DFF040001120405191204190202FF0501070205000000050F"
		hex 82 "01FF0405070F0B0B161616170B0102010C070F1600040D1B1B1B1C16190B0BFF04160D1904040104121212FF06021111FF0404072BFF0707FF0B0F1919011919011919FF050119010101FF0819FF0B0F07070700181B1B180E0F000D0E0000000604120F0F030401111219050101010F02050000000605"
		hex 83 "FF050507190B1616171616160C040400040F1605040C1B1B1B1C0B010BFF05160C0507070007121212FF060211FF0504FF0707FF040F190FFF0819FF12011901FF0719FF080F07070705181B18180D07000D0E0E0000001912040F120401041219FF04010F0201FF040005"
		hex 84 "FF050507010B161617170B00000402000F070E0F07161B1B1C1C0B190B16161617160D0D01040619121212FF050211FF0604FF0507FF050F190F0FFF041901191919FF1701FF0519FF0A0F01171B18180D0F000D0D0E0006010F02120F02020F020201050101010F0201FF040001"
		hex 85 "FF05050701FF0416170D0704020F0B0004040405181B1C1C1C0C010B161616170B010F07070D00FF0602111111FF0504FF0607FF050FFF051901010119FF19011901011919FF090F070F0B1B1B180C0F000D0E000019020203032E0F121203040105010101190201FF040005"
		hex 86 "FF05050705FF05160B0D05000B18170C000D171B1B1C1C1C0C010B16161617160C00000C170C04FF050211FF0504FF0607FF070FFF0419FF0D01050505FF040105FF0C01FF0519FF080F0B1B1B180C0F000D0E000005190F0F0F01050F0707010505010101190201FF0500"
		hex 87 "050605050507050B16161716FF0417181B181B18181B1B1B1C1C1C0C010B161616FF07170B04020202110211FF0404FF04070F07FF050F1919FF0D01FF0F0501010105FF0701190101191919FF060F0D1B18180C07000D0D0D0EFF070006FF0505010101190219FF0500"
		hex 88 "050506060504050B1616161717FF04181B18FF061B1C1C1C0D010B161716FF0717160F0202021102FF0404FF0607FF050F1919010119FF0801FF0A0506FF0A05FF0C01FF0419FF040F00181B180C07000D0D0D0EFF070006FF0605010119020FFF0500"
		hex 89 "050506060504000B1616171717FF04181B23FF051B1C1B1C1B0D010B161617171718FF0517050202110411FF0404FF0407FF050F19190F19010119FF0401FF060506FF060506FF05050605050606050505FF0B01191919FF040F0517181B0B0F000D0D0EFF08000606FF0505010119110FFF0500"
		hex 90 "05050506050400161616FF0417181818FF061B1C1B1C1B1C0D010B1616FF0717181700040211FF04040704070707FF070F191919FF05010501FF050506060506000600060006000006060505FF0406FF0505FF0901FF04190F0F01171818160F050D0D000E0EFF07000606FF0405010119040FFF0500"
		hex 91 "05050506010400161616FF05171818FF071BFF041C0E050B16FF081718170C040211FF0604070707FF050F19FF07010501050505060505060006FF050006FF0800060600060606FF0605FF08011919190F011618180B0F060D0D0EFF08000606050505FF0501040FFF0500"
		hex 92 "FF04050104000B0B0B161616171717FF0618FF061B00010B0BFF0516FF05170B0702020404042BFF0407FF050F191919010101050501FF04050600060606FF150006FF0705FF0901190F190C18170B0705FF090006FF0505FF05011904070000000606"
		hex 93 "0707040704120F0F191919FF0801FF040506050606060F070101FF0905060507FF0404FF05070F0F0FFF0419FF0701FF05050600000006FF1600FF0406FF0605FF0501FF0419010101191107FF060FFF0907FF06041212FF0504"
		hex 94 "FF04190F0207FF050FFF0519FF080105050107010D0C0DFF040CFF060B01FF0404FF0407FF040F19190119FF0401FF06050606FF06000E0000000E0000000EFF0E00FF04060505010505FF0701191901190F0419FF0405FF0A01FF04190F0F0F1112FF0504"
		hex 95 "0C0C0C0B000401FF0600FF050D0C0C0CFF060B0C010D1B1D1C1C1C1D1E1D1DFF041E0B07040404070707FF050F19FF070105050605FF0E000D0E0D0E000EFF0F0006000606050505FF070119010E0D00070D1717FF0616FF060B0C0C0C0D0D0D0E0F110F190F0F0F"
		hex 96 "FF040B000405FF06000D0D0DFF050CFF070B010C1CFF041DFF041E1F1E1E1E180704FF0407FF040F191919FF060105050606FF0A000E0D0D0E0D0EFF080D0E0D0D0DFF0C000606FF0405FF06010E0C00070EFF0517161616FF060BFF040C0D0D0E1902FF0519"
		hex 97 "FF040B000405FF04000EFF040DFF040CFF080B010BFF051D1E1D1DFF041E1F1C1904FF0407FF040F191919FF050105FF0406FF09000EFF120D0E0EFF0B0006FF0405FF0601000D00070EFF05171616FF080B0C0CFF040D1902FF04190F"
		hex 98 "0C0C0B0B050405FF04000E0EFF040DFF050CFF060B010BFF061DFF051E1F1F1D05FF0407FF050F19FF050105050506FF07000EFF090DFF040C0D0C0CFF0C0DFF0800060606050505FF0501000D000F00FF0517161616FF050BFF050C0D0D0D01020F1919190F"
		hex 99 "0B0B0B0C052B05FF0500FF050DFF040CFF070B190B1CFF051DFF081E0DFF0407FF040F1919FF0401050506FF0800FF070D0C0D0C0D0C0BFF050C0D0C0CFF090DFF0A0006FF0405FF0401060D0E0F00FF0517161616FF050BFF050C0D0D0D01020F1919190F"
		hex 100 "0C0C0C0B010705FF05000EFF050D0C0C0CFF060B0C190B1CFF081DFF051E0B0F07FF050F19FF0601050506FF0800FF040D0C0C0D0C0DFF040C0B0C0BFF0A0CFF060D0EFF080006FF0405010101050D000F00FF04171616FF070BFF050C0D0D0D01020F0119190F"
		hex 101 "0C0C0B0B010705FF0500FF04010600050101050DFF040B0C19161CFF041D1B0B0C0B1B1D1B16160E07070F0F0F191919FF050105060606FF05000EFF040DFF060C0B0B0C0C0B0C0C0C0BFF0C0CFF040D0EFF080006050505010101050D000F00FF0417160B06000B0B0B0005050106FF040D0E01020F0119190F"
		hex 102 "0C0C0B0B010706FF040001021202040F060702020700FF040B0C19161C1C1D1D1C0C190F07051B0B1904070707FF040FFF05010505FF04060000000E000D0C0D0D0C0C0C0B0B0C0CFF0F0BFF050C0D0C0D0D0D0E0E0EFF0700FF0505010500000F05FF0417160D04040E0B0C0F0203020FFF050D05020FFF0419"
		hex 103 "FF040C190706FF040006041207010000000411050CFF040B0D0F161CFF041D1817160F04171C0B0705010F0F0F011919010105010506FF05000D0D0D000D0DFF050CFF130B0C0C0C0BFF060C0D0D0E0E0EFF050006060505050101000D0F0517171616160B0F12010C0B0E0F0307000CFF040D05020FFF0419"
		hex 104 "FF040C0F0706FF0500050402010D0D0E0704000C0C0B0B0B0D19161C1C1D1D1D1B160D070F181E18070E000F0F0F19FF0401050606FF07000D0D0D0C0C0D0CFF0D0B1616FF090B0C0BFF050CFF040D0EFF07000606FF0405000E0F051717FF04160002040D0B0B05120F0D0C0C0D0D0E0502071919190F"
		hex 105 "FF040C0F2E06FF0600010204000D0E07040E0C0C0B0B0B0D0F171CFF041D1B060704001D1D17070D0B190F19FF05010506FF06000EFF040D0C0B0CFF0A0B1616FF040B16FF0C0B0C0C0C0D0C0C0D0D0DFF06000606FF040506000F011617FF04160B0F12010B0B05120F0D0CFF040D0602071919190F"
		hex 106 "0D0C0C0C070F05FF060005041201000504070E0CFF040B0D0F171C1C1D1D1D1B180D07051C180C070D170119FF06010506FF05000E0E0D0DFF040CFF060B1616160B1616160B16160BFF0516FF090BFF050C0D0D0E0E0EFF0500060605050506000F0116171616160B0C0002040D0001030F0D0C0D0D0D000602070F19190F"
		hex 107 "0D0C0B0C070F05FF0400010707020201010412070D0C0C0B0B0B0D19181C1C1D1D1C0B0E0004011B0E0F040C1B010F19010105050506FF04000EFF040D0C0C0CFF090BFF07161717FF08160B1616FF060BFF040CFF040D0EFF060006050505000F01161717160B000F0712120119021A07FF060D001107190F0F0F"
		hex 108 "0D0C0C0D070F05FF0400050402020F00000F040F0D0C0C0C0B0B0E19171C1C1D1D1C0B010F0F0B1C18060F161B0019FF0401050505060000000E0D0D0C0C0CFF040B160B0B0BFF0716171717161717171617161617FF0416FF070B0C0C0CFF050D0EFF06000605050019190B1716160B010411021105000F020F0D0CFF040D001107190F0F0F"
		hex 109 "0C0C0C0D070F06FF0500060105000D0D0E0000FF040C0B0B001918FF051C1B1817181C1D1D1C1B1C1D0CFF0401050506050000000D000D0C0CFF060B160BFF07161716FF0A17FF05160B0B160B0B160B0B0BFF050C0D0D0DFF060006060500190F0B171616160B0D0000000C0C0D00000C0C0D0D0D0E000404190F0F0F"
		hex 110 "0C0C0C00040F060606FF05000EFF040DFF060C0B0B0019171B1C1C1CFF091D1E1E1E0BFF04010506FF04000E0D0E0C0C0CFF060BFF0616FF1517FF0416FF050B0C0C0CFF040D0EFF0600060500190F0BFF0416FF070B0C0C0C0D0D0D0E0D00000404FF040F"
		hex 111 "0D0C0C00040F0606FF07000E0D0D0C0C0C0D0CFF040B0019181B1C1C1CFF0B1D1E1705010101050506000D0E0D0D0D0C0C0C0B0B0BFF0616FF06171817171718FF0C171617171616FF050B0C0C0B0C0D0C0D0DFF0600060506190F0B171616FF080B0C0C0CFF050D00060404FF040F"
		hex 112 "0D0D0C0004190606FF08000E0D0D0C0D0D0C0B0B0C0B001918FF061CFF0A1D1B0601050506FF04000E0C0CFF070BFF0416FF041718171717FF06181717181818FF0817FF0416FF070B0C0C0C0D0DFF0600060605190F0B161616FF070BFF040CFF040D0000000711FF040F"
		hex 113 "0D0D0D00041906FF0900FF040DFF070C000118FF061C1D1CFF041D1E1D1D1E1C0D0101060000000E0D0D0D0CFF060BFF0416FF0517181717FF0D18FF0817FF0516FF050B0C0C0C0D0D0D0EFF05000606190F0B161616FF060BFF040CFF040D000E00000702FF040F"
		hex 114 "0D0D0D0604190506FF08000D0EFF050DFF040C0501181BFF051CFF0B1D0C050506FF04000D0C0C0C0B0C0B0B0B161716FF0717FF0D181717181818FF0717FF0516FF040BFF040C0D0D0EFF0500060619070B161616FF060B0C0C0CFF050DFF04000702FF040F"
		hex 115 "0D0D0D05040105050606FF05000E000EFF050DFF040C0101181B1B1BFF041CFF0A1D0B0506FF05000D0D0D0C0B0BFF0416FF06171818181B1818181B1B18FF051BFF07181718FF0517161617160B160B0BFF050C0D0D0DFF0400060601070C1616FF070B0C0C0CFF040D0E0E0000000702FF040F"
		hex 116 "0000000102190101FF050506FF08000EFF040D011917181818FF0B1B1C1C1C160005FF04000D0D0C0CFF040B161616171717181817FF0618FF0B1B181B1BFF0518FF06171616FF040BFF050C0D0D0D0EFF04000601070D0B0BFF050CFF040DFF080006050702070F0707"
		hex 117 "040404020311FF06042BFF0A07FF040F040419FF0F0105050506FF0500FF040C0B0BFF05161717171818171818FF0F1B181B18181B181818FF0517FF0416FF060BFF040C0D0DFF05000102FF0907FF0A04111111031AFF0412"
		hex 118 "070707110219010101FF050506060006FF05000E0E0D0D190701FF05050606FF0F000E0D0D0D0C0B0B0BFF051617FF0618FF161B18181718FF0417FF0516FF040BFF050C0DFF05000104FF090FFF0907FF04040203FF0407"
		hex 119 "0101010704000C0C0CFF040BFF0516FF0617181B1800190C0B0B0CFF080B160BFF04160BFF0400FF040D0B0B0B161616FF0417FF0418FF171BFF0418FF05171617171616FF050B0C0C0C0D0D0EFF0400052E01000606FF0505FF090119190F0F040201060505"
		hex 120 "01010107040D0C0CFF060B1616161717161717171818181706190C0CFF090BFF08160C00000E0D0C0C0CFF050B16FF0417181818FF141B18FF061B18181718FF05171616FF050B0C0C0C0D0D0DFF0400060F01FF0406FF0505FF0801FF0419070201050505"
		hex 121 "19010107070D0C0CFF060B161616FF04171817181818170519FF040CFF090BFF06160C00000D0D0C0C0C0B0B0B1616FF04171818181B18FF081B1CFF041B1C1CFF0C1BFF0418171717161616FF040B0C0B0C0C0D0D0DFF05001901000606FF0505FF0801FF04190F070201050505"
		hex 122 "19010104070D0C0D0CFF060B161616FF0417181717181705190DFF040CFF0D0B160B0000000D0C0C0C0B0B1616171717FF0418FF081B1C1B1B1B1C1B1B1BFF051CFF091BFF0418171717FF0416FF050B0C0C0D0D0D0E0E0000000105000606FF0405FF0901FF04190F071219050505"
		hex 123 "19010104070DFF040CFF050BFF0616FF0417181701190D0C0C0CFF0C0B16160B0B0D000D0D0C0B0B0B1616FF05171818FF091B1C1B1B1BFF091CFF0A1BFF0418FF0417FF0416FF040B0C0C0D0D0D0E0000000501060506050505FF0901FF05190F071219050505"
		hex 124 "191901040F0E0DFF040CFF050BFF0516FF061701190DFF040CFF0E0B160C0E0D0D0C0B0B1616FF0617181B1818FF071BFF0C1C1B1CFF081BFF0518FF0417FF0416FF040B0C0C0C0D0D0E0000000605060505060505FF0901FF04190F0F07120F050501"
		hex 125 "191919110F0E0D0D0C0C0C0D0C0C0CFF060B16FF04171619010DFF060C0D0D0C0B0C0CFF070B0C0E0D0C0CFF040B16171717181818FF061B1C1B1C1B1C1C1C1DFF051C1DFF051CFF091BFF05181717161616FF050B0C0C0C0D0EFF0400060506FF0405FF0601FF0619FF040F07120F050505"
		hex 126 "191919110F0E0D0D0D0C00FF040701050F070F0F0E161717171619010DFF040C000F0707010D060F0F0F19000B0B0B0C0D0D0CFF050B161717FF0518FF051BFF041C1D1C1DFF081C1DFF051CFF081B181818FF0417161616FF040B0C0C0C0D0D0EFF040006FF050519110419010F11020202040F190F0F0F07120F050501"
		hex 127 "0F190F020F0EFF040D05121A040701010312070F0016161717160F010DFF040C050F0F040201190202070F00FF040B0C0C0B160B0B1616FF04171818FF041B1C1C1B1C1C1D1C1CFF061D1C1D1D1DFF081CFF071B18181817171716171616FF040B0C0CFF040D00000006FF0405011912030F010F0310030204FF050F07120F050501"
		hex 128 "19190F020F00FF040D00070307000C000412010C0B161717170B0F010E0D0D0D0C0D00000F120F000702010DFF050B0C0D0C0B0B0BFF0416171818FF051B1C1C1C1B1C1D1D1C1D1D1CFF051D1C1DFF071CFF081B181818FF04171616160B0B0BFF040C0D0D0EFF0400050505010101041A041919041A0307FF060F071207010101"
		hex 129 "0F190F020F000EFF040D000403190C0B0004020016161617170B0F010EFF050D050F1102050C06040406FF050B0C0D0CFF040B16171718181B1B1B1C1B1BFF071C1D1D1C1CFF051D1C1D1D1DFF071CFF061BFF0418171717161616FF040B0C0C0C0D0D0DFF04000505FF04010F03030F010F111A12FF060F071207010101"
		hex 130 "0F0F0F02190000FF050D011202000B0B0112070CFF04160B0F010EFF050D01041204000C0D0102070DFF040B0C050C17171716FF0417181B181B1C1C1B1B1C1C1D1C1CFF0E1DFF071CFF051BFF0418FF051716160B0B0BFF040C0D0D0EFF0400FF0405010101041A0419190F121011FF050F071207010101"
		hex 131 "0F0F0F021900000E0D0D0000050203010D0D0512020D0B1616160B0701000EFF040D00050402050E0005020400FF040B0C0F0CFF061B0B05060DFF04181B1B1B1C1CFF121DFF061CFF071B1818FF04171616FF040B0C0C0C0D0D0DFF040005FF0501190703030F0F0F111003FF050F071204010101"
		hex 132 "0F0F0712010000000E0E01111103120519041103040D0B1616160C070100000D0D0D050707020205010404120400FF040B0D0F0CFF061B160F0207160D19190F001B1C1C1D1D1C1C1CFF0A1D1C1D1DFF041C1B1CFF051B181818FF0417161616FF050B0C0C0D0D0EFF040005FF040104021210100402121A1012FF050F071204010101"
		hex 133 "0F0F0702010000000E0D050402020F0D01040204050B0B0B16160C070100000E0D0D06070404190005070407010D0B0B0B0C0D0F0CFF071B0C0F05170B01070F0DFF051B180F0017181B1B1C1CFF071DFF051C1B1B1CFF041B181818171717161616FF050B0C0C0D0D0EFF040005FF04010412120312070412031204FF050F070204010101"
		hex 134 "0F0F070201FF04000E000006000E0C0D0E000DFF050B160C070100000E0E0D0D0006000D0D0D0000000DFF050C0D0F0BFF081B17181B1B181617FF061B17120F0C0CFF050B16171818FF061B1C1CFF061BFF0418FF041716160B0B0BFF040C0D0DFF040006FF040119FF070F0707FF050F07070202010101"
		hex 135 "0F0F070201FF06000E0D0D0DFF050CFF050B160D040100000E0E00000D0EFF070DFF060C000F0CFF151B161207FF080C0DFF040C0B0B0B16161717181817181B1B18FF05171616FF040BFF040C0D0EFF040006FF050119011919FF0A0F07070202190101"
		hex 136 "0F0F04020106FF05000E0E0D0DFF050CFF060B0D0401FF06000EFF060D0C0D0D0DFF040C000F0CFF151B170307FF060C0D0C0D0D0CFF0B0D0100FF05171617171616FF050B0C0C0D0D0D0E00000006FF0501FF0419FF080F070F07070202190101"
		hex 137 "0F0F04020106FF0700FF040D0C0C0CFF060B0E0401FF07000D0D0E0D000EFF050D0C0C0C00070CFF091B231B1B18FF081B160307FF040C0D0C0CFF090D0E0E0D0E00000705FF0816FF060B0C0C0C0D0D0EFF050005010101FF0519FF080FFF040702120F0119"
		hex 138 "07070402010606FF06000EFF050D0C0C0B0B0C0B0B000401FF08000E0E0D0EFF060D0C0C0C00070B18181BFF0418FF061B181823181B1B1B181603070D0C0D0C0C0CFF0A0D000EFF040007010BFF0416FF090BFF040C0D0D0E00000506FF0401FF0419FF090FFF040702120F1919"
		hex 139 "07071102010506FF05000EFF070DFF040C0B0B000401FF0A00FF0B0D00070C18181BFF04181B18181B18181B1818181B1818180B03070D0CFF0B0D0E0EFF070007010B1616FF090BFF060C0D0D0D0E1904FF0401FF0419FF090FFF050702030F1919"
		hex 140 "070702020105060606FF0600FF050DFF040C0B0B06040106FF0B000EFF080D00070BFF051817FF0F18160307FF090D0E0D0E0E0EFF080007010B161616FF070BFF050CFF060D0F11190101FF0419FF090FFF060702030F1919"
		hex 141 "040412120F0F0FFF0419FF08010505060505000019020FFF1001FF0505010406FF0D0C0B0BFF060C001002FF0C05FF0A01040FFF0B00060606FF0705010702FF09070407FF09041102121A040707"
		hex 142 "030310100303FF0812FF0A021111020311FF0A042BFF0A07041204FF1507042003FF0E07040707FF05040202FF0A04FF0411FF0802031AFF0502FF0612031212FF08031A0A1A1A1A"
		hex 143 "0F0F020304FF08072EFF080FFF0419071105000E00FF080D0C0DFF060C0B0B0004010600060600FF0906000606000606060110070C0C0B0B0C0C0BFF080CFF060D0E0704FF0A01FF0419FF080F0402FF0A01190F1919FF070F07041A020202"
		hex 144 "01190212070707FF080F191919FF08010F040D0CFF060B160B0B160BFF0516171617160C0705000D0D0E0E0E0D0EFF040D00FF040E0D0E000E061A0F16FF0617FF0B16FF040B19070505060506FF0505FF0B011907020600000600000606FF0505FF07011919071A020404"
		hex 145 "19190212070707FF080F191919FF080107040D0CFF090B160B0BFF08160D070500000E00000E0D000D0E0E0D0E0E0E000E0000000D061A0F16171617FF0E16FF040B1907FF09050105FF0A0119070205000006000006FF0405FF090119190703020404"
		hex 146 "190F0212FF0407FF080F191919FF070107040D0C0C0CFF0A0BFF08160D0705FF0B000E0E00000EFF050005100FFF0C16FF0A0B1907FF0805FF0C01191907020500FF0506FF0405FF090119190703020404"
		hex 147 "190F1202FF0507FF070F191919FF070107040DFF050CFF0C0BFF04160D0705FF150001100FFF0C16FF0A0B1907FF0605FF0D011919190702010000060606FF0405FF0801FF04190F03020404"
		hex 148 "0F0F0302FF0607FF080F1919FF060104070E0D0D0C0C0CFF0E0B1616000401FF150005100FFF0616FF0F0B0C190401050505010105FF0B011919190F070201060606FF0505FF0A0119190F0F03120404"
		hex 149 "0F0F0302FF06072E2EFF060F191919FF05010407000D0DFF050CFF0D0B160E0401FF150005100F1616FF120B0C0C19040105FF0E01FF06190712010606FF0505FF0801FF05190F0F03120404"
		hex 150 "0F07030204FF09070F0F07070F0FFF0419010104070EFF060D00000D0C0C0D0D0D0CFF060B000401FF080006060000050505FF060001100FFF060B0C0D0C0B0B0C0D0D0C0C0B0B0B0C0C0C1904FF07011919190101190F0FFF05190F0F071201FF0505FF0601190F0F0F1919190F19190F03030411"
		hex 151 "0F07030204FF040704120303031104120312040FFF051904070EFF040D000F04040F00000F0404190DFF050B0004050006FF0500060F0F051904110401FF050001100FFF050B0507040F000C0107040F000C0B0B0C0C0C1904FF0601070202040F07021202070F19190F0F0F071219FF0405010F0204010119020303020F19FF050F03031111"
	}
}

