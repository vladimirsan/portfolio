using FigaroLib.Kernel.Debug;
using FigaroLib.RPG.Characters;
using System;
using System.Collections.Generic;
using System.Xml.Linq;
using System.Linq;


namespace FigaroLib.RPG.Data
{
    public class DataSystem
    {
        #region members

        private Dictionary<int, PokemonData> characterCatalog;
        private Dictionary<int, List<Pokemon_move>> pokemon_moveCatalog;
        private Dictionary<int, MoveData> moveCatalog;
        private Dictionary<int, ItemData> itemCatalog;

        private Dictionary<KeyValuePair<PokemonType, PokemonType>, float> typeRelationCatalog;
        //-------------------------------------------------------------

        public int PokemonCatalogCount
        {
            get { return characterCatalog.Count; }
        }

        public int MoveCatalogCount
        {
            get { return moveCatalog.Count; }
        }

        public int ItemCatalogCount
        {
            get { return itemCatalog.Count; }
        }

        public int typeRelationCount
        {
            get { return typeRelationCatalog.Count; }
        }

        public int getPokemon_moveCountById(int id)
        {
            fAssert.assert(pokemon_moveCatalog.ContainsKey(id),
                "Trying to obtain pokemon_move data for an invalid pokemon");

            return pokemon_moveCatalog[id].Count;
        }

        #endregion

        public DataSystem()
        {
        }

        public void start()
        {
            //La creacion de los objetos esta aca porque si no da problemas con el unit testing
            characterCatalog = new Dictionary<int, PokemonData>();
            pokemon_moveCatalog = new Dictionary<int, List<Pokemon_move>>();
            moveCatalog = new Dictionary<int, MoveData>();
            typeRelationCatalog = new Dictionary<KeyValuePair<PokemonType, PokemonType>, float>();
            itemCatalog = new Dictionary<int, ItemData>();


            loadPokemonCatalog();
            loadPokemon_moveCatalog();
            loadMoveCatalog();
            loadTypeRelationCatalog();
            loadItemCatalog();
        }

        public PokemonData getPokemonData(int id)
        {
            fAssert.assert(characterCatalog.ContainsKey(id),
                "Trying to load a non-existent character");
            return characterCatalog[id];
        }

        public ItemData getItem(int id)
        {
            fAssert.assert(itemCatalog.ContainsKey(id),
                "Trying to load a non-existent item");
            return itemCatalog[id];
        }

        public MoveData getMoveData(int id)
        {
            fAssert.assert(moveCatalog.ContainsKey(id),
                "Trying to load an invalid move id");
            return moveCatalog[id];
        }

        public float getTypeRelationMultiplier(PokemonType a, PokemonType d)
        {
            fAssert.assert(a != PokemonType.Null && d != PokemonType.Null,
                "Can't search for a type relation for a null type");

            if (a == PokemonType.Normal)
                return 1;

            KeyValuePair<PokemonType, PokemonType> typeRelation =
                new KeyValuePair<PokemonType, PokemonType>(a, d);
            fAssert.assert(typeRelationCatalog.ContainsKey(typeRelation),
                "Trying to read a non-existing type relation');");

            return typeRelationCatalog[typeRelation];
        }

        public List<int> getPokemonMovesPerLevel(int pokemonId, int level)
        {
            fAssert.assert(characterCatalog.ContainsKey(pokemonId),
                "trying to obtain data for an invalid pokemon_move");

            if (pokemon_moveCatalog.ContainsKey(pokemonId))
            {
                var movesByLevel = from pokemon_move in pokemon_moveCatalog[pokemonId]
                                   where pokemon_move.level == level
                                   select pokemon_move.moveId;
                return movesByLevel.ToList<int>();
            }
            return new List<int>();
        }

        private void loadItemCatalog()
        {
            XElement xmlData;
            try
            {
                xmlData = getXElementFromFile("item.xml");
                var query = from item in xmlData.Elements() select item;

                foreach (var item in query)
                {
                    ItemData parsedItem = new ItemData();
                    foreach (var field in item.Descendants("field"))
                    {
                        switch (field.Attribute("name").Value)
                        {
                            case "id":
                                parsedItem.id = int.Parse(field.Value);
                                break;
                            case "name":
                                parsedItem.name = field.Value;
                                break;
                            case "description":
                                parsedItem.description = field.Value;
                                break;
                        }
                    }
                    itemCatalog.Add(parsedItem.id, parsedItem);
                }
            }
            catch (System.Exception e)
            {
                ErrorManager.manageException("Can't load XML data -- itemCatalog", e);
            };
        }

        private void loadPokemonCatalog()
        {
            XElement xmlData;
            try
            {
                xmlData = getXElementFromFile("pokemon.xml");
                var query = from pokemon in xmlData.Elements() select pokemon;

                foreach (var pokemon in query)
                {
                    PokemonData parsedPokemon = new PokemonData();
                    foreach (var field in pokemon.Descendants("field"))
                    {
                        switch (field.Attribute("name").Value)
                        {
                            case "id":
                                parsedPokemon.id = int.Parse(field.Value);
                                break;
                            case "name":
                                parsedPokemon.name = field.Value;
                                break;
                            case "baseHp":
                                parsedPokemon.baseHp = int.Parse(field.Value);
                                break;
                            case "baseAttack":
                                parsedPokemon.baseAttack = int.Parse(field.Value);
                                break;
                            case "baseDefense":
                                parsedPokemon.baseDefense = int.Parse(field.Value);
                                break;
                            case "baseSpeed":
                                parsedPokemon.baseSpeed = int.Parse(field.Value);
                                break;
                            case "baseSpecial":
                                parsedPokemon.baseSpecial = int.Parse(field.Value);
                                break;
                            case "typeId1":
                                parsedPokemon.typeId1 = int.Parse(field.Value);
                                break;
                            case "typeId2":
                                parsedPokemon.typeId2 = int.Parse(field.Value);
                                break;
                        }
                    }
                    characterCatalog.Add(parsedPokemon.id, parsedPokemon);
                }
            }
            catch (System.Exception e)
            {
                ErrorManager.manageException("Can't load XML data -- pokemonCatalog", e);
            };
        }

        private void loadPokemon_moveCatalog()
        {
            XElement xmlData;
            try
            {
                xmlData = getXElementFromFile("pokemon_move.xml");
                var query = from pokemon_move in xmlData.Elements() select pokemon_move;
                int pId = -1;

                foreach (var pokemon_move in query)
                {
                    Pokemon_move pm = new Pokemon_move();
                    foreach (var field in pokemon_move.Descendants("field"))
                    {
                        switch (field.Attribute("name").Value)
                        {
                            case "pokemonId":
                                pId = int.Parse(field.Value);
                                break;
                            case "moveId":
                                pm.moveId = int.Parse(field.Value);
                                break;
                            case "level":
                                pm.level = int.Parse(field.Value);
                                break;
                        }
                    }

                    fAssert.assert(pId != -1 && pm.level != -1 && pm.moveId != -1,
                        "Trying to store pokemon_move with invalid data");
                    if (pokemon_moveCatalog.ContainsKey(pId))
                    {
                        pokemon_moveCatalog[pId].Add(pm);
                    }
                    else
                    {
                        List<Pokemon_move> list = new List<Pokemon_move>();
                        list.Add(pm);
                        pokemon_moveCatalog.Add(pId, list);
                    }
                }
            }
            catch (System.Exception e)
            {
                ErrorManager.manageException("Can't load XML data -- pokemon_move", e);
            };

            foreach (List<Pokemon_move> pokemon_moveList in pokemon_moveCatalog.Values)
            {
                pokemon_moveList.Sort();
            }
        }

        private void loadMoveCatalog()
        {
            XElement xmlData;
            try
            {
                xmlData = getXElementFromFile("move.xml");
                var query = from move in xmlData.Elements() select move;

                foreach (var move in query)
                {
                    MoveData moveData = new MoveData();
                    foreach (var field in move.Descendants("field"))
                    {
                        switch (field.Attribute("name").Value)
                        {
                            case "id":
                                moveData.id = int.Parse(field.Value);
                                break;
                            case "name":
                                moveData.name = field.Value;
                                break;
                            case "basePower":
                                moveData.basePower = int.Parse(field.Value);
                                break;
                            case "accuracy":
                                moveData.accuracy = int.Parse(field.Value);
                                break;
                            case "pp":
                                moveData.pp = int.Parse(field.Value);
                                break;
                            case "typeId":
                                moveData.typeId = int.Parse(field.Value);
                                fAssert.assert(moveData.typeId != 0,
                                    "Trying to create a move with null type");
                                break;
                            case "description":
                                moveData.description = field.Value;
                                break;
                        }
                    }
                    moveCatalog.Add(moveData.id, moveData);
                }
            }
            catch (System.Exception e)
            {
                ErrorManager.manageException("Can't load XML data -- moveCatalog", e);
            };
        }

        private void loadTypeRelationCatalog()
        {
            XElement xmlData;
            try
            {
                xmlData = getXElementFromFile("type_type.xml");
                var query = from type_type in xmlData.Elements() select type_type;

                //Esto se hace porque la carajada no deja crear y modificar despues los valores del key-value
                PokemonType key = PokemonType.Null;
                PokemonType value = PokemonType.Null;
                float multiplier = 1;

                foreach (var type_type in query)
                {
                    foreach (var field in type_type.Descendants("field"))
                    {
                        switch (field.Attribute("name").Value)
                        {
                            case "typeIdA":
                                key = (PokemonType)int.Parse(field.Value);
                                break;
                            case "typeIdD":
                                value = (PokemonType)int.Parse(field.Value);
                                break;
                            case "multiplier":
                                multiplier = float.Parse(field.Value);
                                break;
                        }
                    }
                    KeyValuePair<PokemonType, PokemonType> typeRelation =
                        new KeyValuePair<PokemonType, PokemonType>(key, value);
                    typeRelationCatalog.Add(typeRelation, multiplier);
                }
            }
            catch (System.Exception e)
            {
                ErrorManager.manageException("Can't load XML data -- typeRelation", e);
            };
        }

        private XElement getXElementFromFile(String path)
        {
            return XElement.Load(path);
        }
    }
}
