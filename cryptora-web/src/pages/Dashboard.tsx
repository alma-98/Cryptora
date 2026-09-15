export default function Dashboard() {
  return (
    <section style={pageStyle}>
      <h1>Dashboard</h1>

      <p style={muted}>
        Cryptora Native Blockchain overview.
      </p>

      <div style={gridStyle}>
        <Card title="Native Asset" value="CRC" />
        <Card title="Network" value="Cryptora Native" />
        <Card title="Blockchain" value="ONLINE" />
        <Card title="Wallet Layer" value="ACTIVE" />
      </div>
    </section>
  );
}

function Card({
  title,
  value
}: {
  title: string;
  value: string;
}) {
  return (
    <div style={cardStyle}>
      <small>{title}</small>
      <h2>{value}</h2>
    </div>
  );
}

const pageStyle = {
  padding: "32px",
  fontFamily: "Inter, system-ui, sans-serif"
};

const muted = {
  color: "#64748b"
};

const gridStyle = {
  display: "grid",
  gridTemplateColumns:
    "repeat(auto-fit,minmax(200px,1fr))",
  gap: "16px"
};

const cardStyle = {
  background: "white",
  padding: "24px",
  borderRadius: "14px",
  border: "1px solid #e2e8f0"
};
