CREATE OR REPLACE FUNCTION add_componentstorage_from_supply() RETURNS trigger AS $$
BEGIN
    IF NOT EXISTS (SELECT 1 FROM "ComponentStorages" WHERE "WarehouseId" = NEW."WarehouseId" AND "Price" = NEW."SupplyPrice") THEN
        INSERT INTO "ComponentStorages" ("Price", "Amount", "ComponentId", "WarehouseId") VALUES (NEW."SupplyPrice", NEW."Amount", NEW."ComponentId", NEW."WarehouseId");
    ELSE
        UPDATE "ComponentStorages" SET "Amount" = "Amount" + NEW."Amount" WHERE "WarehouseId" = NEW."WarehouseId" AND "Price" = NEW."SupplyPrice";
    END IF;
	RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trigger_supplies_insert
AFTER INSERT ON "Supplies"
FOR EACH ROW
EXECUTE FUNCTION add_componentstorage_from_supply();