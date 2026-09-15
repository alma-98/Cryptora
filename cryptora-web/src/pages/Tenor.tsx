export default function Tenor() {
  return (
    <section style={pageStyle}>
      <h1>Tenor</h1>

      <p style={muted}>
        Administrator-controlled transaction tenor.
      </p>

      <div style={card}>
        <p>30 Days</p>
        <p>60 Days</p>
        <p>90 Days</p>
      </div>
    </section>
  );
}

const pageStyle = {
  padding: "32px",
  fontFamily: "Inter, system-ui, sans-serif"
};

const muted = {
  color: "#64748b"
};

const card = {
  marginTop: "20px",
  background: "white",
  padding: "24px",
  borderRadius: "14px",
  border: "1px solid #e2e8f0"
};
